// MyShooterGame


#include "Weapon/ShooterLauncherWeaponActor.h"
#include "Weapon/ShooterProjectile.h"
#include "Kismet/GameplayStatics.h"

void AShooterLauncherWeaponActor::StartFire()
{
	MakeShot();
}

void AShooterLauncherWeaponActor::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AShooterProjectile* Projectile = GetWorld()->SpawnActorDeferred<AShooterProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	DecreaseAmmo();
	SpawnMuzzleFX();
}
