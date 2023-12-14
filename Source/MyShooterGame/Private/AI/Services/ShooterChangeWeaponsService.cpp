// MyShooterGame


#include "AI/Services/ShooterChangeWeaponsService.h"
#include "AIController.h"
#include "ShooterUtiles.h"
#include "Components/ShooterWeaponComponent.h"

UShooterChangeWeaponsService::UShooterChangeWeaponsService()
{
	NodeName = "ChangeWeapon";
}

void UShooterChangeWeaponsService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability )
		{
			WeaponComponent->NextWeapon();
		}
	}


	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
