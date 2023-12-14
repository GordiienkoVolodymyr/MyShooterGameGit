// MyShooterGame


#include "Menu/UI/Shooter_Menu_Widget.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter_Game_Instance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuInstance, All, All);


void UShooter_Menu_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Start_Game_Button)
	{
		Start_Game_Button->OnClicked.AddDynamic(this, &UShooter_Menu_Widget::On_Start_Game);
	}

	if (Quit_Game_Button)
	{
		Quit_Game_Button->OnClicked.AddDynamic(this, &UShooter_Menu_Widget::On_Quit_Game);
	}

	Init_Level_Items();
}

void UShooter_Menu_Widget::On_Start_Game()
{
	PlayAnimation(HideAnimation);
	
}

void UShooter_Menu_Widget::On_Quit_Game()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UShooter_Menu_Widget::Init_Level_Items()
{
	const auto Shooher_Game_Instance = Get_Shooter_Game_Instance();

	if (!Shooher_Game_Instance)
	{
		return;
	}

	checkf(Shooher_Game_Instance->Get_Levels_Data().Num() !=0, TEXT("Levels dat must not be empty"));

	if (!Level_Item_Box)
	{
		return;
	}
	Level_Item_Box->ClearChildren();

	for (auto LevelData : Shooher_Game_Instance->Get_Levels_Data())
	{
		const auto Level_Item_Widget = CreateWidget<UShooter_Level_Item_Widget>(GetWorld(), Level_Item_Widget_Class);
		if (!Level_Item_Widget)
		{
			continue;
		}
		Level_Item_Widget->Set_Level_Data(LevelData);
		Level_Item_Widget->OnLevelSelected.AddUObject(this, &UShooter_Menu_Widget::On_Level_Selected);

		Level_Item_Box->AddChild(Level_Item_Widget);
		Level_Item_Widgets.Add(Level_Item_Widget);
	}

	if (Shooher_Game_Instance->Get_Start_Level_Name().Level_Name.IsNone())
	{
		On_Level_Selected(Shooher_Game_Instance->Get_Levels_Data()[0]);
	}
	else
	{
		On_Level_Selected(Shooher_Game_Instance->Get_Start_Level_Name());
	}
}

void UShooter_Menu_Widget::On_Level_Selected(const FLevelData &Data)
{
	const auto Shooher_Game_Instance = Get_Shooter_Game_Instance();

	if (!Shooher_Game_Instance)
	{
		return;
	}

	Shooher_Game_Instance->Set_Start_Level(Data);

	/*for (auto Level_Item_Widget : Level_Item_Widgets)
	{
		if (Level_Item_Widget)
		{
			const auto IsSelected = Data.Level_Name == Level_Item_Widget->Get_Level_Data().Level_Name;
		}
	}*/
}

UShooter_Game_Instance* UShooter_Menu_Widget::Get_Shooter_Game_Instance() const
{
	if (!GetWorld())
	{
		return nullptr;
	}
	return GetWorld()->GetGameInstance<UShooter_Game_Instance>();

}

void UShooter_Menu_Widget::OnAnimationFinished_Implementation(const UWidgetAnimation *Animation)
{
	//Super::OnAnimationFinished_Implementation(Animation);
	if (Animation != HideAnimation)
	{
		return;
	}

	const auto Shooher_Game_Instance = Get_Shooter_Game_Instance();

	if (!Shooher_Game_Instance)
	{
		return;
	}

	UGameplayStatics::OpenLevel(this, Shooher_Game_Instance->Get_Start_Level_Name().Level_Name);
}
