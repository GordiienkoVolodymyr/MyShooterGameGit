// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Shooter_Health_Bar_AI_Widget.generated.h"


UCLASS()
class MYSHOOTERGAME_API UShooter_Health_Bar_AI_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Set_Health_Percent(float percent);

protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar *Heath_Progress_Bar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float Percent_Visibility_Threshold = 0.8;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float Percent_Color_Threshold = 0.3;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor Good_Color = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor Bad_Color = FLinearColor::Red;

};
