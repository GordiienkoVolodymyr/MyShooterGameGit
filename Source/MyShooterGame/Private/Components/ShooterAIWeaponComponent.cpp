// MyShooterGame


#include "Components/ShooterAIWeaponComponent.h"
#include "Weapon/ShooterBaseWeaponActor.h"

void UShooterAIWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}
	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void UShooterAIWeaponComponent::NextWeapon()
{
	if (!CanEquip())
	{
		return;
	}
	int64 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty())
		{
			break;
		}
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
