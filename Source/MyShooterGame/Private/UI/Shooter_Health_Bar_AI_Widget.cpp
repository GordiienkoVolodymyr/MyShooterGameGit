// MyShooterGame


#include "UI/Shooter_Health_Bar_AI_Widget.h"

void UShooter_Health_Bar_AI_Widget::Set_Health_Percent(float percent)
{
	if (!Heath_Progress_Bar)
	{
		return;
	}
	ESlateVisibility Health_Bar_Visibility;

	if (percent > Percent_Visibility_Threshold || FMath::IsNearlyZero(percent))
	{
		Health_Bar_Visibility = ESlateVisibility::Hidden;
	}
	else
	{
		Health_Bar_Visibility = ESlateVisibility::Visible;
	}
	Heath_Progress_Bar->SetVisibility(Health_Bar_Visibility);

	FLinearColor Health_Bar_Color;
	if (percent > Percent_Color_Threshold)
	{
		Health_Bar_Color = Good_Color;
	}
	else
	{
		Health_Bar_Color = Bad_Color;
	}

	Heath_Progress_Bar->SetFillColorAndOpacity(Health_Bar_Color);

	Heath_Progress_Bar->SetPercent(percent);
}
