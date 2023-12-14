// MyShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Player/ShooterCharacter.h"
#include "Components/WidgetComponent.h"
#include "ShooterAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class MYSHOOTERGAME_API AShooterAICharacter : public AShooterCharacter
{
	GENERATED_BODY()
public:
	AShooterAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaivorTreeAsset;

		virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	virtual void OnDeath() override;

	virtual void OnHealthChanged(float Health, float HealthDelta) override; 

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Components")
	UWidgetComponent *Health_Widget_Component;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	float Health_Visible_Distance = 1000.0f;

private:
	void Update_Health_Widget_Visibility();
};
