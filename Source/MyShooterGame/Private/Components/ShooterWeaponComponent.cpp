// MyShooterGame


#include "Components/ShooterWeaponComponent.h"
#include "Weapon/ShooterBaseWeaponActor.h"
#include "GameFramework/Character.h"
#include "Animations/ShooterEquipFinishedAnimNotify.h"
#include "Animations/ShooterReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponStatic, All, All);

constexpr static int64 WeaponConst = 2;

UShooterWeaponComponent::UShooterWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UShooterWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponConst, TEXT("Our character can hold only 2 weapon item"), WeaponConst);

	CurrentWeaponIndex = 0;
	InitAnimation();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UShooterWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void UShooterWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UShooterWeaponComponent::SpawnWeapons()
{

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld())
	{
		return;
	}

	for (auto OneWeaponData : WeaponData)
	{	
		auto Weapon = GetWorld()->SpawnActor<AShooterBaseWeaponActor>(OneWeaponData.WeaponClass);
		if (!Weapon)
		{
			continue;
		}
		Weapon->OnClipEmpty.AddUObject(this, &UShooterWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSoket(Weapon, Character->GetMesh(), WeaponArmorySoketName);

	}

	if (!CurrentWeapon)
	{
		return;
	}	
}

void UShooterWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}
	CurrentWeapon->StartFire();
}

void UShooterWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->StopFire();
}

void UShooterWeaponComponent::AttachWeaponToSoket(AShooterBaseWeaponActor* Weapon, USceneComponent* SceneComponent,
	const FName& SoketName)
{
	if (!Weapon || !SceneComponent)
	{
		return;
	}
	FAttachmentTransformRules AttachmentRulls(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRulls, SoketName);
}

void UShooterWeaponComponent::EquipWeapon(int64 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponStatic, Warning, TEXT("Invalid weapon index"));
		return;
	}
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}
	if (CurrentWeapon)
	{
		CurrentWeapon->Zoom(false);
		CurrentWeapon->StopFire();
		AttachWeaponToSoket(CurrentWeapon, Character->GetMesh(), WeaponArmorySoketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	//CurrentreloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
		{return Data.WeaponClass == CurrentWeapon->GetClass(); });
	CurrentreloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	AttachWeaponToSoket(CurrentWeapon, Character->GetMesh(), WeaponEquipSoketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UShooterWeaponComponent::NextWeapon()
{
	if (!CanEquip())
	{
		return;
	}
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UShooterWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	Character->PlayAnimMontage(Animation);
}

void UShooterWeaponComponent::InitAnimation()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifybyClass<UShooterEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotifySignature.AddUObject(this, &UShooterWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponStatic, Error, TEXT("Equip anim notify is fogotten to set"));
		checkNoEntry();
	}
	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifybyClass<UShooterReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponStatic, Error, TEXT("Reload anim notify is fogotten to set"));
			checkNoEntry();
		}
		ReloadFinishedNotify->OnNotifySignature.AddUObject(this, &UShooterWeaponComponent::OnReloadFinished);
	}
}

void UShooterWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	if (Character->GetMesh() == MeshComp)
	{
		EquipAnimInProgress = false;
	}
}

void UShooterWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	if (Character->GetMesh() == MeshComp)
	{
		ReloadAnimInProgress = false;
	}
}

bool UShooterWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UShooterWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;
}

bool UShooterWeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void UShooterWeaponComponent::Reload()
{
	ChangeClip();
}

void UShooterWeaponComponent::OnEmptyClip(AShooterBaseWeaponActor* AmmoEmptyWeapon)
{
	if (!AmmoEmptyWeapon)
	{
		return;
	}

	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			if (Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}
}

void UShooterWeaponComponent::ChangeClip()
{
	if (!CanReload())
	{
		return;
	}
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentreloadAnimMontage);
}

bool UShooterWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
			UIData = CurrentWeapon->GetUIData();
			return true;
	}
	return false;
}

bool UShooterWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

bool UShooterWeaponComponent::TryToAddAmmo(TSubclassOf<AShooterBaseWeaponActor> WeaponType, int64 ClipsAmount)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;
}

bool UShooterWeaponComponent::NeedAmmo(TSubclassOf<AShooterBaseWeaponActor> WeaponType)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}
	return false;
}

void UShooterWeaponComponent::Zoom(bool Enable)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Zoom(Enable);
	}
}
