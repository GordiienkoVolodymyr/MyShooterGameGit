// MyShooterGame


#include "Weapon/ShooterProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/ShooterWeaponFXComponent.h"

// Sets default values
AShooterProjectile::AShooterProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	WeaponProjectileFXComponent = CreateDefaultSubobject<UShooterWeaponFXComponent>("WeaponProjectileFXComponent");
}

void AShooterProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponProjectileFXComponent);
	MovementComponent->Velocity = ShootDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AShooterProjectile::OnProjectileHit);
	SetLifeSpan(LifeSpawn);
}

void AShooterProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())
	{
		return;
	}

	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), RadiusDamage, 
		UDamageType::StaticClass(), {GetOwner()}, this, GetController(), DoFullDamage);

	// закоментировать после добавления ефектов взрыва 
	DrawDebugSphere(GetWorld(), GetActorLocation(), RadiusDamage, 24, FColor::Red, false, 5.0f);

	WeaponProjectileFXComponent->PlayImpactFX(Hit);
	Destroy();

}

AController* AShooterProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}


