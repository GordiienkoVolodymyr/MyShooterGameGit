// MyShooterGame


#include "UI/Shooter_Player_Stat_Row_Widget.h"

void UShooter_Player_Stat_Row_Widget::Set_Name_Player(const FText &name)
{
	if (!Name_Text_Block)
	{
		return;
	}
	Name_Text_Block->SetText(name);
}

void UShooter_Player_Stat_Row_Widget::Set_Kills_Player(const FText &kills)
{
	if (!Kills_Text_Block)
	{
		return;
	}
	Kills_Text_Block->SetText(kills);
}

void UShooter_Player_Stat_Row_Widget::Set_Deaths_Player(const FText &deaths)
{
	if (!Deaths_Text_Block)
	{
		return;
	}
	Deaths_Text_Block->SetText(deaths);
}

void UShooter_Player_Stat_Row_Widget::Set_Team_Player(const FText &team)
{
	if (!Team_Text_Block)
	{
		return;
	}
	Team_Text_Block->SetText(team);
}

void UShooter_Player_Stat_Row_Widget::Set_Indicator_Image(bool visible)
{
	if (!Player_Indicator_Image)
	{
		return;
	}
	if (visible)
	{
		Player_Indicator_Image->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Player_Indicator_Image->SetVisibility(ESlateVisibility::Hidden);
	}
}
