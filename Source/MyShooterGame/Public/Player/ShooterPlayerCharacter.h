// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Player/ShooterCharacter.h"
#include "ShooterPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class MYSHOOTERGAME_API AShooterPlayerCharacter : public AShooterCharacter
{
	GENERATED_BODY()
	
public:
	AShooterPlayerCharacter(const FObjectInitializer& ObjInit);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* CameraCollisionComponent;
	virtual void OnDeath() override;

	virtual void BeginPlay() override;

private:
	void MoveForward(float Amount);
	void MoveRightLeft(float Amount);

	bool WantsToRun = false;
	bool IsMovingForward = false;
	void OnStartRun();
	void OnStopRun();

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ChechCameraOverlap();
};
