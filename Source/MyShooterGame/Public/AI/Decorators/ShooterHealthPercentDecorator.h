// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ShooterHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooterHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UShooterHealthPercentDecorator();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		float HealthPercent = 0.6f;
};
