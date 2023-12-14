// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShooterBaseWeaponActor.h"
#include "ShooterLauncherWeaponActor.generated.h"

class AShooterProjectile;

UCLASS()
class MYSHOOTERGAME_API AShooterLauncherWeaponActor : public AShooterBaseWeaponActor
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AShooterProjectile> ProjectileClass;
	virtual void MakeShot() override;


};
