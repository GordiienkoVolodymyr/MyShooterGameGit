// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UShooterAIPerceptionComponent;
class UShooterRespawnComponent;

UCLASS()
class MYSHOOTERGAME_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AShooterAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UShooterAIPerceptionComponent* ShooterAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		FName FocusOnKeyName = "EnemyActor";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UShooterRespawnComponent* RespawnComponent;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;
};
