// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterSpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooterSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetRespawnTime(int64& RespawnTime) const;
};
