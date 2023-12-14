// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterCoreTypes.h"
#include "ShooterWeaponComponent.generated.h"
class AShooterBaseWeaponActor;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTERGAME_API UShooterWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShooterWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
	bool TryToAddAmmo(TSubclassOf<AShooterBaseWeaponActor> WeaponType, int64 ClipsAmount);
	bool NeedAmmo(TSubclassOf<AShooterBaseWeaponActor> WeaponType);
	void Zoom(bool Enable) ;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	 TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponEquipSoketName = "WeaponSoket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySoketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* EquipAnimMontage;
	UPROPERTY()
		AShooterBaseWeaponActor* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<AShooterBaseWeaponActor*> Weapons;

	bool CanFire() const;
	bool CanEquip() const;
	void EquipWeapon(int64 WeaponIndex);
	int64 CurrentWeaponIndex = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		UAnimMontage* CurrentreloadAnimMontage = nullptr;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void SpawnWeapons();

	void AttachWeaponToSoket(AShooterBaseWeaponActor* Weapon, USceneComponent* SceneComponent,const FName& SoketName);

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimation();

	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	bool CanReload() const;

	void OnEmptyClip(AShooterBaseWeaponActor* AmmoEmptyWeapon);
	void ChangeClip();
};
