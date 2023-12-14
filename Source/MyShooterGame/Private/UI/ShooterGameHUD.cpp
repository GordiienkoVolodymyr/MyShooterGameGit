// MyShooterGame


#include "UI/ShooterGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include <MyShooterGame/ShooterGameModeBase.h>

DEFINE_LOG_CATEGORY_STATIC(LogMatchState, All, All);

void AShooterGameHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrossHair();
}

void AShooterGameHUD::BeginPlay()
{
	Super::BeginPlay();

	Game_Widgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	Game_Widgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), Pause_Widget_Class));
	Game_Widgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), Game_Over_Widget_Class));

	for (auto widget : Game_Widgets)
	{
		const auto Game_Widget = widget.Value;
		if (!Game_Widget)
		{
			continue;
		}

		Game_Widget->AddToViewport();
		Game_Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto Game_Mode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (Game_Mode)
		{
			Game_Mode->OnMatchStateChanged.AddUObject(this, &AShooterGameHUD::On_Match_State_Changed);
		}
	}
}

void AShooterGameHUD::DrawCrossHair()
{
	const TInterval<float> Centre(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	const float HalflineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(Centre.Min - HalflineSize, Centre.Max, Centre.Min + HalflineSize, Centre.Max, LineColor, LineThickness);
	DrawLine(Centre.Min , Centre.Max - HalflineSize, Centre.Min , Centre.Max + HalflineSize, LineColor, LineThickness);
}

void AShooterGameHUD::On_Match_State_Changed(ESTUMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Game_Widgets.Contains(State))
	{
		CurrentWidget = Game_Widgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}

	UE_LOG(LogMatchState, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
