// MyShooterGame


#include "Weapon/ShooterRifleWeaponActor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/ShooterWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AShooterRifleWeaponActor::AShooterRifleWeaponActor()
{
	WeaponFXComponent = CreateDefaultSubobject<UShooterWeaponFXComponent>("WeaponFXComponent");
}


void AShooterRifleWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

void AShooterRifleWeaponActor::StartFire()
{
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AShooterRifleWeaponActor::MakeShot, TimeBetweenShot, true);
	MakeShot();
}

void AShooterRifleWeaponActor::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXVisible(false);
}

void AShooterRifleWeaponActor::Zoom(bool Enabled)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if (!Controller || !Controller->PlayerCameraManager)
	{
		return;
	}


	
	if (Enabled)
	{
		Deefault_Camera_FOV = Controller->PlayerCameraManager->GetFOVAngle();
	}
	
	Controller->PlayerCameraManager->SetFOV(Enabled ? FOV_Zoom : Deefault_Camera_FOV);
}

void AShooterRifleWeaponActor::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	DecreaseAmmo();
}

bool AShooterRifleWeaponActor::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceStart = ViewLocation;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}


void AShooterRifleWeaponActor::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor)
	{
		return;
	}
	DamageActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), false);
}

void AShooterRifleWeaponActor::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleFXVisible(true);
}

void AShooterRifleWeaponActor::SetMuzzleFXVisible(bool Visible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visible);
		MuzzleFXComponent->SetVisibility(Visible, true);
	}
}

void AShooterRifleWeaponActor::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* AShooterRifleWeaponActor::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

