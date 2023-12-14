// MyShooterGame


#include "Player/ShooterPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogStatistics, All, All);

void AShooterPlayerState::LogInfo()
{
	UE_LOG(LogStatistics, Display, TEXT("TeamID: %i, KillsNum: %i, DeathNum: %i"), TeamID, KillsNum, DeathNum);
}
