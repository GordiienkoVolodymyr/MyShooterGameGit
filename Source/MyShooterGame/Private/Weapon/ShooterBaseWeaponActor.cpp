// MyShooterGame


#include "Weapon/ShooterBaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AShooterBaseWeaponActor::AShooterBaseWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(WeaponMeshComponent);
}

void AShooterBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMeshComponent);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count could'nt ne less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count could'nt ne less or equal zero"));
	CurrentAmmo = DefaultAmmo;
}

void AShooterBaseWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterBaseWeaponActor::StartFire()
{

}

void AShooterBaseWeaponActor::StopFire()
{
}

void AShooterBaseWeaponActor::MakeShot()
{

}

APlayerController* AShooterBaseWeaponActor::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
	{
		return nullptr;
	}
	return Player->GetController<APlayerController>();
}

bool AShooterBaseWeaponActor::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto ShooterCharacter = Cast<ACharacter>(GetOwner());
	if (!ShooterCharacter)
	{
		return false;
	}

	if (ShooterCharacter->IsPlayerControlled())
	{
		const auto Controller = GetPlayerController();
		if (!Controller)
		{
			return false;
		}
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMeshComponent->GetSocketRotation(MuzzleSoketName);
	}


	return true;
}

FVector AShooterBaseWeaponActor::GetMuzzleWorldLocation() const
{
	return WeaponMeshComponent->GetSocketLocation(MuzzleSoketName);
}

bool AShooterBaseWeaponActor::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}
	const FVector ShootDirection = ViewRotation.Vector();
	TraceStart = ViewLocation;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AShooterBaseWeaponActor::MakeHit(FHitResult& HitResult ,FVector& TraceStart, FVector& TraceEnd)
{
	if (!GetWorld())
	{
		return;
	}
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

}

void AShooterBaseWeaponActor::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("fgdgdfgdf"));
		return;
	}
	CurrentAmmo.Bullets--;

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}

bool AShooterBaseWeaponActor::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite &&  CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AShooterBaseWeaponActor::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void AShooterBaseWeaponActor::ChangeClip()
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{		
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool AShooterBaseWeaponActor::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips;
}

void AShooterBaseWeaponActor::LogAmmo()
{
	FString AmmoInfo = "Ammo : " + FString::FromInt(CurrentAmmo.Bullets) + "/";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool AShooterBaseWeaponActor::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool AShooterBaseWeaponActor::TryToAddAmmo(int64 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <=0)
	{
		return false;
	}
	if (IsAmmoEmpty())
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("Ammo was empty"));
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if (DefaultAmmo.Clips - NextClipsAmount >=0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
			UE_LOG(LogBaseWeapon, Display, TEXT("Clips was added"));

		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
			UE_LOG(LogBaseWeapon, Display, TEXT("Ammo is full now"));
		}
	}
	else
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("Bullets was added"));
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	return true;
}

UNiagaraComponent* AShooterBaseWeaponActor::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, WeaponMeshComponent, MuzzleSoketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}