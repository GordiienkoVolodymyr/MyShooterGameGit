// MyShooterGame


#include "UI/ShooterPlayerHUDWidget.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"
#include "ShooterUtiles.h"


void UShooterPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UShooterPlayerHUDWidget::OneNewPawn);
		OneNewPawn(GetOwningPlayerPawn());
	}

}

void UShooterPlayerHUDWidget::OneNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UShooterPlayerHUDWidget::OnHealthChanged);
	}
}

void UShooterPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
}

float UShooterPlayerHUDWidget::GetHealthPerent() const
{
	const auto HealthComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent)
	{
		return 0.0f;
	}

	return HealthComponent->GetHealthPercent();
}

bool UShooterPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UShooterPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterWeaponComponent>(GetOwningPlayerPawn());

	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool UShooterPlayerHUDWidget::IsPlayerALive() const
{
	const auto HealthComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UShooterPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}

