// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterBasePickUp.generated.h"

class USphereComponent;

UCLASS()
class MYSHOOTERGAME_API AShooterBasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	AShooterBasePickUp();
	bool CouldBeTaken() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
		USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
		float RespawnTime = 5.0f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	float RotationYaw = 0.0f;
	void GenerateRotationYaw();
	virtual bool GivePickUpTrue(APawn* PlayerPawn);
	void PickUpWasTaken();
	void Respawn();
	FTimerHandle RespawnTimer;
};
