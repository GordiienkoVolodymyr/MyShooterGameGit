// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "ShooterCoreTypes.h"
#include "Menu/UI/Shooter_Level_Item_Widget.h"
#include "Shooter_Game_Instance.h"
#include "Shooter_Menu_Widget.generated.h"


UCLASS()
class MYSHOOTERGAME_API UShooter_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void On_Start_Game();

	UFUNCTION()
	void On_Quit_Game();

	void Init_Level_Items();

	void On_Level_Selected(const FLevelData &Data);

	UShooter_Game_Instance* Get_Shooter_Game_Instance() const;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation *Animation) override;

	UPROPERTY(meta = (BindWidget))
	UButton *Start_Game_Button;

	UPROPERTY(meta = (BindWidget))
	UButton *Quit_Game_Button;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox *Level_Item_Box;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Level_Item_Widget_Class;

	UPROPERTY()
	TArray<UShooter_Level_Item_Widget *> Level_Item_Widgets;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation *HideAnimation;
};
