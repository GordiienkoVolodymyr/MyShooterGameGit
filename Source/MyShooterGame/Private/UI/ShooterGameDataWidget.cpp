// MyShooterGame


#include "UI/ShooterGameDataWidget.h"
#include <MyShooterGame/ShooterGameModeBase.h>
#include "ShooterPlayerState.h"

int64 UShooterGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetShooterGameMode();
	return GameMode ? GameMode->GetCurrentRoundsNum() : 0;
}

int64 UShooterGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetShooterPlayerState();
	return PlayerState ? PlayerState->GetKills() : 0;
}

int64 UShooterGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetShooterGameMode();
	return GameMode ? GameMode->GetGameData().RoundsMax : 0;
}

int64 UShooterGameDataWidget::GetRoundSecondRemaning() const
{
	const auto GameMode = GetShooterGameMode();
	return GameMode ? GameMode->GetCurrentRoundTimeNum() : 0;
}

AShooterGameModeBase* UShooterGameDataWidget::GetShooterGameMode() const
{
	return GetWorld() ? Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AShooterPlayerState* UShooterGameDataWidget::GetShooterPlayerState() const
{
	return GetOwningPlayer() ? Cast<AShooterPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
