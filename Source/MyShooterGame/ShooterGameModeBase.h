// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/ShooterCoreTypes.h"
#include "ShooterGameModeBase.generated.h"

class AAIController;

UCLASS()
class MYSHOOTERGAME_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AShooterGameModeBase();
	FOnMatchStateChangedSignature OnMatchStateChanged;

	virtual void StartPlay() override; 
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);

	FGameData GetGameData() const { return GameData; }
	int64 GetCurrentRoundsNum() const { return CurrentRound; }
	int64 GetCurrentRoundTimeNum() const { return RoundCountDown; }

	void RespawnRequest(AController* Controller);
	virtual bool SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		FGameData GameData;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		TSubclassOf<APawn> AIPawnClass;

private:
	void SpawnBot();
	void StartRound();
	void GameTimerUpdate();
	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);
	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int64 Id) const;
	void SetPlayerCollor(AController* Controller);
	void LogPlayerInfo();
	void StartRespaw(AController* Controller);
	void GameOver();
	void Set_Match_State(ESTUMatchState State);


	FTimerHandle GameRoundTimerHandle;
	int64 CurrentRound = 1;
	int64 RoundCountDown = 0;
	ESTUMatchState Match_State = ESTUMatchState::WaitingToStart;
};
