// MyShooterGame


#include "Player/ShooterCharacter.h"
#include "Components/ShooteCharacterMovementComponent.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Components/ShooterWeaponComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AShooterCharacter::AShooterCharacter(const FObjectInitializer& ObjInit) : 
	Super(ObjInit.SetDefaultSubobjectClass<UShooteCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShooterHealthComponent = CreateDefaultSubobject<UShooterHealthComponent>("ShooterHealthComponent");
	WeaponComponent = CreateDefaultSubobject<UShooterWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(ShooterHealthComponent->GetHealth(), 0.0f);
	ShooterHealthComponent->OnDeath.AddUObject(this, &AShooterCharacter::OnDeath);
	ShooterHealthComponent->OnHealthChanged.AddUObject(this, &AShooterCharacter::OnHealthChanged);
	
	LandedDelegate.AddDynamic(this, &AShooterCharacter::OnGroundLanded);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input


bool AShooterCharacter::IsRunning() const
{
	return false;
}

float AShooterCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
	{
		return 0.0f;
	}
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}



void AShooterCharacter::OnDeath()
{
	//PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifeSpawnOnDeath);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AShooterCharacter::OnHealthChanged(float Health, float HealthDelta)
{
}

void AShooterCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	if (FallVelocityZ < LandedDamageVelocity.X)
	{
		return;
	}
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AShooterCharacter::SetPlayerColor(FLinearColor Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst)
	{
		return;
	}

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}
