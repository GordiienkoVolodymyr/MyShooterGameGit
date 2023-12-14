// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Menu_Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API AMenu_Player_Controller : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
