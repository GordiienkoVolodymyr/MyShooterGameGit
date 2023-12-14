// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Shooter_Menu_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API AShooter_Menu_HUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Menu_Widget_Class;
};
