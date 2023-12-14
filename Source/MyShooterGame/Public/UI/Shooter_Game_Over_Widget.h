// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterCoreTypes.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Shooter_Game_Over_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooter_Game_Over_Widget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox *Player_Stat_Box;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Player_Stat_Row_Widget_Class;

	UPROPERTY(meta = (BindWidget))
	UButton *Reset_Level_Button;

	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void On_Reset_level();

private:
	void On_Match_State_Changed(ESTUMatchState State);
	void Update_Player_Stat();
};
