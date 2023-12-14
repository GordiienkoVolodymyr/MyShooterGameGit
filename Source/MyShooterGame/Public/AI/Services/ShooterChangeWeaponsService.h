// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShooterChangeWeaponsService.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooterChangeWeaponsService : public UBTService
{
	GENERATED_BODY()
	
public:
	UShooterChangeWeaponsService();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float Probability = 0.5;
};
