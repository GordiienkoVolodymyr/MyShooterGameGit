// MyShooterGame


#include "Menu/UI/Shooter_Level_Item_Widget.h"


void UShooter_Level_Item_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Level_Select_Button)
	{
		Level_Select_Button->OnClicked.AddDynamic(this, &UShooter_Level_Item_Widget::On_Level_Clicked);
	}
}

void UShooter_Level_Item_Widget::On_Level_Clicked()
{
	OnLevelSelected.Broadcast(Level_Data);
}

void UShooter_Level_Item_Widget::Set_Level_Data(const FLevelData &Data)
{
	Level_Data = Data;

	if (Level_Name_Text_Block)
	{
		Level_Name_Text_Block->SetText(FText::FromName(Data.Level_Display_Name));
	}

	if (Image_Level)
	{
		Image_Level->SetBrushFromTexture(Data.LevelThumb);
	}

}

//void UShooter_Level_Item_Widget::Set_Selected(bool is_selected)
//{
//	if (FrameImage)
//	{
//		FrameImage->SetVisibility(ESlateVisibility::Visible);
//	}
//	else
//	{
//		FrameImage->SetVisibility(ESlateVisibility::Hidden);
//
//	}
//}

