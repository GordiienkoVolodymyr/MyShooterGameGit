// MyShooterGame


#include "AI/Decorators/ShooterFindAmmoDecorator.h"
#include "AIController.h"
#include "ShooterUtiles.h"
#include "Components/ShooterWeaponComponent.h"

UShooterFindAmmoDecorator::UShooterFindAmmoDecorator()
{
	NodeName = "Find Ammo";
}

bool UShooterFindAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
	{
		return false;
	}

	const auto WeaponComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->NeedAmmo(WeaponType);
}

