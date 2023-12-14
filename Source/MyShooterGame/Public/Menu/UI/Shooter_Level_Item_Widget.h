// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ShooterCoreTypes.h"
#include "Shooter_Level_Item_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooter_Level_Item_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnLevelSelectedSignature OnLevelSelected;

	void Set_Level_Data(const FLevelData &Data);

	FLevelData Get_Level_Data() const { return Level_Data; }

	//void Set_Selected(bool is_selected);

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton *Level_Select_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Level_Name_Text_Block;

	UPROPERTY(meta = (BindWidget))
	UImage *Image_Level = 0;

	UFUNCTION()
	void On_Level_Clicked();

private:
	FLevelData Level_Data;
};
