// MyShooterGame


#include "AI/ShooterAIController.h"
#include "AI/ShooterAICharacter.h"
#include "Components/ShooterAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ShooterRespawnComponent.h"


AShooterAIController::AShooterAIController()
{
	ShooterAIPerceptionComponent = CreateDefaultSubobject<UShooterAIPerceptionComponent>("ShooterAIPerceptionComponent");
	SetPerceptionComponent(*ShooterAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<UShooterRespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto ShooterCharacter = Cast<AShooterAICharacter>(InPawn);

	if (ShooterCharacter)
	{
		RunBehaviorTree(ShooterCharacter->BehaivorTreeAsset);
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AShooterAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent())
	{
		return nullptr;
	}
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}

