// MyShooterGame


#include "AI/Services/ShooterFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterUtiles.h"
#include "Components/ShooterAIPerceptionComponent.h"


UShooterFindEnemyService::UShooterFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UShooterFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (BlackBoard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = ShooterUtiles::GetShooterPlayerComponent<UShooterAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosesEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
