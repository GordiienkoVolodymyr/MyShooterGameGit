// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "ShooterAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTERGAME_API UShooterAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClosesEnemy() const;
	
};
