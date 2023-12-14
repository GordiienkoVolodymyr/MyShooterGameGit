// MyShooterGame


#include "AI/Decorators/ShooterHealthPercentDecorator.h"
#include "AIController.h"
#include "ShooterUtiles.h"
#include "Components/ShooterHealthComponent.h"


UShooterHealthPercentDecorator::UShooterHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool UShooterHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
	{
		return false;
	}

	const auto HealthComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterHealthComponent>(Controller->GetPawn());
	if (!HealthComponent && HealthComponent->IsDead())
	{
		return false;
	}


	return HealthComponent->GetHealthPercent() <= HealthPercent;
}


