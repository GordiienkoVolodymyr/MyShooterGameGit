// MyShooterGame


#include "UI/ShooterSpectatorWidget.h"
#include "ShooterUtiles.h"
#include "Components/ShooterRespawnComponent.h"

bool UShooterSpectatorWidget::GetRespawnTime(int64& RespawnTime) const
{
	const auto RespawnComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterRespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
	{
		return false;
	}

	RespawnTime = RespawnComponent->GetRespawnTimerCountDown();
	return true;
}
