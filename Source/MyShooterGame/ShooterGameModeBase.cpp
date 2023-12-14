// MyShooterGame


#include "ShooterGameModeBase.h"
#include "Player/ShooterCharacter.h"
#include "Player/ShooterPlayerController.h"
#include "UI/ShooterGameHUD.h"
#include "AIController.h"
#include "Player/ShooterPlayerState.h"
#include "ShooterUtiles.h"
#include "Components/ShooterRespawnComponent.h"
#include "EngineUtils.h"
#include "Shooter_Game_Instance.h"

DEFINE_LOG_CATEGORY_STATIC(GameStatics, All, All);

constexpr static int64 MinRoundTimerForRespawn = 10;

AShooterGameModeBase::AShooterGameModeBase()
{
	DefaultPawnClass = AShooterCharacter::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
	HUDClass = AShooterGameHUD::StaticClass();
	PlayerStateClass = AShooterPlayerState::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	SpawnBot();
	CreateTeamsInfo();
	CurrentRound = 1;
	StartRound();

	Set_Match_State(ESTUMatchState::InProgress);
}

UClass* AShooterGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShooterGameModeBase::SpawnBot()
{
	if (!GetWorld())
	{
		return;
	}

	for (int64 i = 0; i < GameData.PlayersNum-1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto ShooterAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(ShooterAIController);
	}
}

void AShooterGameModeBase::StartRound()
{
	RoundCountDown = GameData.TimeRound;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AShooterGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AShooterGameModeBase::GameTimerUpdate()
{
	UE_LOG(GameStatics, Display, TEXT("Time: %i / Round: %i / %i"), RoundCountDown, CurrentRound, GameData.RoundsMax);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
		if (CurrentRound + 1 <= GameData.RoundsMax)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
			
		}
	}
}

void AShooterGameModeBase::ResetPlayers()
{
	if (!GetWorld())
	{
		return;
	}

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AShooterGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerCollor(Controller);
}

void AShooterGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld())
	{
		return;
	}

	int64 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
		{
			continue;
		}

		const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
		if (!PlayerState)
		{
			continue;
		}

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		if (Controller->IsPlayerController())
		{
			PlayerState->SetPlayerName("Player");
		}
		else
		{
			PlayerState->SetPlayerName("Bot");
		}
		SetPlayerCollor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor AShooterGameModeBase::DetermineColorByTeamID(int64 Id) const
{
	if (Id - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[Id - 1];
	}
	return GameData.DefaultColor;
}

void AShooterGameModeBase::SetPlayerCollor(AController* Controller)
{
	if (!Controller)
	{
		return;
	}

	const auto Character = Cast<AShooterCharacter>(Controller->GetPawn());
	if (!Character)
	{
		return;
	}

	const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
	if (!PlayerState)
	{
		return;
	}
	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AShooterGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AShooterPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<AShooterPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespaw(VictimController);
}

void AShooterGameModeBase::LogPlayerInfo()
{
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
		{
			continue;
		}

		const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
		if (!PlayerState)
		{
			continue;
		}

		PlayerState->LogInfo();
	}
}

void AShooterGameModeBase::StartRespaw(AController* Controller)
{
	const auto RespawnAvalible = RoundCountDown > MinRoundTimerForRespawn + GameData.RespawnTime;
	if (!RespawnAvalible)
	{
		return;
	}
	const auto Respawn = ShooterUtiles::GetShooterPlayerComponent<UShooterRespawnComponent>(Controller);
	if (!Respawn)
	{
		return;
	}

	Respawn->Respawn(GameData.RespawnTime);
}

void AShooterGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

void AShooterGameModeBase::GameOver()
{
	UE_LOG(GameStatics, Display, TEXT("-----------Game Over---------------"));
	LogPlayerInfo();
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
	Set_Match_State(ESTUMatchState::GameOver);
}

void AShooterGameModeBase::Set_Match_State(ESTUMatchState State)
{
	if ( Match_State == State)
	{
		return;
	}

	Match_State = State;
	OnMatchStateChanged.Broadcast(Match_State);
}

bool AShooterGameModeBase::SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate)
{
	const auto Pause_Set = Super::SetPause(PC, CanUnpauseDelegate);
	if (Pause_Set)
	{
		Set_Match_State(ESTUMatchState::Pause);
	}
	return Pause_Set;
}

bool AShooterGameModeBase::ClearPause()
{
	const auto Pause_Cleard = Super::ClearPause();
	if (Pause_Cleard)
	{
		Set_Match_State(ESTUMatchState::InProgress);
	}
	return Pause_Cleard;
}
