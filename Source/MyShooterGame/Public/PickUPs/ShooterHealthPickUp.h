// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "ShooterBasePickUp.h"
#include "ShooterHealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API AShooterHealthPickUp : public AShooterBasePickUp
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
		float HealthAmount = 50.f;
private:
	virtual bool GivePickUpTrue(APawn* PlayerPawn) override;
};
