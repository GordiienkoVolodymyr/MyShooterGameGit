// MyShooterGame


#include "UI/Shooter_Pause_Widget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UShooter_Pause_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Clear_Pause_Button)
	{
		Clear_Pause_Button->OnClicked.AddDynamic(this, &UShooter_Pause_Widget::On_Clear_Pause);
	}
}

void UShooter_Pause_Widget::On_Clear_Pause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}

	GetWorld()->GetAuthGameMode()->ClearPause();
}
