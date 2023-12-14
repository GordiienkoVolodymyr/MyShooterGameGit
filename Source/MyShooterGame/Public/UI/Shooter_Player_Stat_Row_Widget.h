// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Shooter_Player_Stat_Row_Widget.generated.h"


UCLASS()
class MYSHOOTERGAME_API UShooter_Player_Stat_Row_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set_Name_Player(const FText &name);
	void Set_Kills_Player(const FText &kills);
	void Set_Deaths_Player(const FText &deaths);
	void Set_Team_Player(const FText &team);
	void Set_Indicator_Image(bool visible);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock *Name_Text_Block;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Kills_Text_Block;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Deaths_Text_Block;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *Team_Text_Block;

	UPROPERTY(meta = (BindWidget))
	UImage *Player_Indicator_Image;
};
