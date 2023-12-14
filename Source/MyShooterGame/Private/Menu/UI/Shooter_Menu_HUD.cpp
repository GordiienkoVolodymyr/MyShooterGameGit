// MyShooterGame


#include "Menu/UI/Shooter_Menu_HUD.h"
#include "Blueprint/UserWidget.h"

void AShooter_Menu_HUD::BeginPlay()
{
	Super::BeginPlay();

	const auto Menu_Widget = CreateWidget<UUserWidget>(GetWorld(), Menu_Widget_Class);
	if (Menu_Widget)
	{
		Menu_Widget->AddToViewport();
	}
}
