// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterCoreTypes.h"
#include "ShooterGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API AShooterGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Pause_Widget_Class;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Game_Over_Widget_Class;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<ESTUMatchState, UUserWidget*> Game_Widgets;

	UPROPERTY()
	UUserWidget *CurrentWidget = 0;
	void DrawCrossHair();
	void On_Match_State_Changed(ESTUMatchState State);
};
