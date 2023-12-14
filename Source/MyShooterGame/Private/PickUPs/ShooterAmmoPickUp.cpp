// MyShooterGame


#include "PickUPs/ShooterAmmoPickUp.h"
#include "Components/ShooterWeaponComponent.h"
#include "Components/ShooterHealthComponent.h"
#include "ShooterUtiles.h"
DEFINE_LOG_CATEGORY_STATIC(LogPickUp, All, All);

bool AShooterAmmoPickUp::GivePickUpTrue(APawn* PlayerPawn)
{
    const auto HealthComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
    {
        return false;
    }
    const auto WeaponComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterWeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
    {
        return false;
    }
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
