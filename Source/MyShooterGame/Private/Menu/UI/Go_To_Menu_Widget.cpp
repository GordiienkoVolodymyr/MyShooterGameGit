// MyShooterGame


#include "Menu/UI/Go_To_Menu_Widget.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter_Game_Instance.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameInstance, All, All);

void UGo_To_Menu_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Return_To_Menu_Button)
	{
		Return_To_Menu_Button->OnClicked.AddDynamic(this, &UGo_To_Menu_Widget::Return_To_Menu);
	}
}

void UGo_To_Menu_Widget::Return_To_Menu()
{
	if (!GetWorld())
	{
		return;
	}
	const auto Shooter_Game_Instance = GetWorld()->GetGameInstance<UShooter_Game_Instance>();
	if (!Shooter_Game_Instance)
	{
		return;
	}

	if (Shooter_Game_Instance->Get_Menu_Level_Name().IsNone())
	{
		UE_LOG(LogGameInstance, Display, TEXT("Level name is None"));
		return;
	}

	UGameplayStatics::OpenLevel(this, Shooter_Game_Instance->Get_Menu_Level_Name());

}
