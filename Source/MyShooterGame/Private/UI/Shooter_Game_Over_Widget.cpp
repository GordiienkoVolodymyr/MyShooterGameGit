// MyShooterGame


#include "UI/Shooter_Game_Over_Widget.h"
#include <MyShooterGame/ShooterGameModeBase.h>
#include "Player/ShooterPlayerState.h"
#include "UI/Shooter_Player_Stat_Row_Widget.h"
#include "Player/ShooterPlayerState.h"
#include <ShooterUtiles.h>
#include "Kismet/GameplayStatics.h"

void UShooter_Game_Over_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		const auto Game_Mode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (Game_Mode)
		{
			Game_Mode->OnMatchStateChanged.AddUObject(this, &UShooter_Game_Over_Widget::On_Match_State_Changed);
		}
	}

	if (Reset_Level_Button)
	{
		Reset_Level_Button->OnClicked.AddDynamic(this, &UShooter_Game_Over_Widget::On_Reset_level);
	}
}

void UShooter_Game_Over_Widget::On_Match_State_Changed(ESTUMatchState State)
{
	if (State == ESTUMatchState::GameOver)
	{
		Update_Player_Stat();
	}
}

void UShooter_Game_Over_Widget::Update_Player_Stat()
{
	if (!GetWorld() || !Player_Stat_Box)
	{
		return;
	}

	Player_Stat_Box->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; It++)
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
		const auto PlayerStatRowWidget = CreateWidget<UShooter_Player_Stat_Row_Widget>(GetWorld(), Player_Stat_Row_Widget_Class);
		if (!PlayerStatRowWidget)
		{
			continue;
		}
		PlayerStatRowWidget->Set_Name_Player(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->Set_Kills_Player(FText::FromString(FString::FromInt(PlayerState->GetKills())));
		PlayerStatRowWidget->Set_Deaths_Player(FText::FromString(FString::FromInt(PlayerState->GetDeath())));
		PlayerStatRowWidget->Set_Team_Player(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
		PlayerStatRowWidget->Set_Indicator_Image(Controller->IsPlayerController());

		Player_Stat_Box->AddChild(PlayerStatRowWidget);
	}
}

void UShooter_Game_Over_Widget::On_Reset_level()
{
	//const FName Current_Level_Name = "TestLevel";
	const FString Current_Level_Name = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(Current_Level_Name));
}
