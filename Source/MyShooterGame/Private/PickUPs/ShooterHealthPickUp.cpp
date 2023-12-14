// MyShooterGame


#include "PickUPs/ShooterHealthPickUp.h"
#include "Components/ShooterHealthComponent.h"
#include "ShooterUtiles.h"


bool AShooterHealthPickUp::GivePickUpTrue(APawn* PlayerPawn)
{
    const auto HealthComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterHealthComponent>(PlayerPawn);
    if (!HealthComponent)
    {
        return false;
    }
    return HealthComponent->TryToAddHealth(HealthAmount);
}
