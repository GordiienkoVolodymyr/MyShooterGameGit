// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterGameDataWidget.generated.h"

class AShooterGameModeBase;
class AShooterPlayerState;

UCLASS()
class MYSHOOTERGAME_API UShooterGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int64 GetCurrentRoundNum() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int64 GetKillsNum() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int64 GetTotalRoundsNum() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int64 GetRoundSecondRemaning() const;

private:

	AShooterGameModeBase* GetShooterGameMode() const;
	AShooterPlayerState* GetShooterPlayerState() const;

};
