// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterCoreTypes.h"
#include "ShooterPlayerController.generated.h"

class UShooterRespawnComponent;

UCLASS()
class MYSHOOTERGAME_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShooterPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UShooterRespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	void On_Pause_Game();
	void On_Match_State_Changed(ESTUMatchState State);
};
