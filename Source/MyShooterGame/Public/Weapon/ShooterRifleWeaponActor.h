// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShooterBaseWeaponActor.h"
#include "ShooterRifleWeaponActor.generated.h"

class UShooterWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class MYSHOOTERGAME_API AShooterRifleWeaponActor : public AShooterBaseWeaponActor
{
	GENERATED_BODY()

public:
	AShooterRifleWeaponActor();
	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void Zoom(bool Enabled) override;
protected:
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	virtual void BeginPlay() override;

	UPROPERTY()
	UNiagaraComponent *MuzzleFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShot = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UShooterWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FOV_Zoom = 50.0f;

private:
	void MakeDamage(const FHitResult& HitResult);
	void InitMuzzleFX();
	void SetMuzzleFXVisible(bool Visible);
	void SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd);

	AController* GetController() const;
	FTimerHandle ShotTimerHandle;
	float Deefault_Camera_FOV = 90.0f;
};

