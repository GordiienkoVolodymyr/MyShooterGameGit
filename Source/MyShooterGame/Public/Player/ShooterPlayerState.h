// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShooterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API AShooterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetTeamID(int64 Id) { TeamID = Id; }
	int64 GetTeamID() const { return TeamID; }

	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	FLinearColor GetTeamColor() const { return TeamColor; }

	void AddKill() { ++KillsNum; }
	void AddDeath() { ++DeathNum; }

	int64 GetKills() const { return KillsNum; }
	int64 GetDeath() const { return DeathNum; }

	void LogInfo();

private:
	int64 TeamID;
	int64 KillsNum = 0;
	int64 DeathNum = 0;
	FLinearColor TeamColor;
};
