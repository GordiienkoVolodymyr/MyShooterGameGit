// MyShooterGame


#include "ShooterBasePickUp.h"
#include "Components/SphereComponent.h"



AShooterBasePickUp::AShooterBasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}


void AShooterBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);
	GenerateRotationYaw();
}


void AShooterBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}


void AShooterBasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickUpTrue(Pawn))
	{
		PickUpWasTaken();
	}
}

bool AShooterBasePickUp::GivePickUpTrue(APawn* PlayerPawn)
{
	return false;
}

void AShooterBasePickUp::PickUpWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (CollisionComponent)
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	
	
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &AShooterBasePickUp::Respawn, RespawnTime);
}

void AShooterBasePickUp::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (CollisionComponent)
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}

void AShooterBasePickUp::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

bool AShooterBasePickUp::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimer);
}
