// MyShooterGame


#include "Player/ShooterPlayerController.h"
#include "Components/ShooterRespawnComponent.h"
#include <MyShooterGame/ShooterGameModeBase.h>

AShooterPlayerController::AShooterPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UShooterRespawnComponent>("RespawnComponent");
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		const auto Game_Mode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (Game_Mode)
		{
			Game_Mode->OnMatchStateChanged.AddUObject(this, &AShooterPlayerController::On_Match_State_Changed);
		}
	}
}

void AShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent)
	{
		return;
	}

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AShooterPlayerController::On_Pause_Game);
}

void AShooterPlayerController::On_Pause_Game()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AShooterPlayerController::On_Match_State_Changed(ESTUMatchState State)
{
	if (State == ESTUMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
