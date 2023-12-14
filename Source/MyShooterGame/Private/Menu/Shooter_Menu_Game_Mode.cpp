// MyShooterGame


#include "Menu/Shooter_Menu_Game_Mode.h"
#include "Menu/Menu_Player_Controller.h"
#include "Menu/UI/Shooter_Menu_HUD.h"

AShooter_Menu_Game_Mode::AShooter_Menu_Game_Mode()
{
	PlayerControllerClass = AMenu_Player_Controller::StaticClass();
	HUDClass = AShooter_Menu_HUD::StaticClass();
}
