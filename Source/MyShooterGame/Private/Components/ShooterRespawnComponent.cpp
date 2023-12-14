// MyShooterGame


#include "Components/ShooterRespawnComponent.h"
#include <MyShooterGame/ShooterGameModeBase.h>

UShooterRespawnComponent::UShooterRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterRespawnComponent::Respawn(int64 RespawnTime)
{
	if (!GetWorld())
	{
		return;
	}
	RespawnTimerCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &UShooterRespawnComponent::RespawnTimeUpdate, 1.0f, true);

}


void UShooterRespawnComponent::RespawnTimeUpdate()
{
	if (--RespawnTimerCountDown == 0)
	{
		if (!GetWorld())
		{
			return;
		}
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimer);

		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode)
		{
			return;
		}

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}

bool UShooterRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(RespawnTimer);
}