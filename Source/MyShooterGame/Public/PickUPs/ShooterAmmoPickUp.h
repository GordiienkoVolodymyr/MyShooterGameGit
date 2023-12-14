// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "ShooterBasePickUp.h"
#include "ShooterAmmoPickUp.generated.h"

class AShooterBaseWeaponActor;

UCLASS()
class MYSHOOTERGAME_API AShooterAmmoPickUp : public AShooterBasePickUp
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
		int64 ClipsAmount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
		TSubclassOf<AShooterBaseWeaponActor> WeaponType;


private:
	virtual bool GivePickUpTrue(APawn* PlayerPawn) override;
};
