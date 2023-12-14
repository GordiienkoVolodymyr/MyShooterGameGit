// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ShooterFindAmmoDecorator.generated.h"

class AShooterBaseWeaponActor;

UCLASS()
class MYSHOOTERGAME_API UShooterFindAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UShooterFindAmmoDecorator();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<AShooterBaseWeaponActor> WeaponType;
};
