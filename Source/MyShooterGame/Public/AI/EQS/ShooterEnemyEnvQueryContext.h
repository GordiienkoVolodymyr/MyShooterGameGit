// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "ShooterEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooterEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		FName EnemyActorKeyName = "EnemyActor";
};
