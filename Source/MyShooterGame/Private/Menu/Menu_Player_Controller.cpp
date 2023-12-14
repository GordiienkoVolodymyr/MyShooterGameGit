// MyShooterGame


#include "Menu/Menu_Player_Controller.h"
#include "Shooter_Game_Instance.h"

void AMenu_Player_Controller::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}
