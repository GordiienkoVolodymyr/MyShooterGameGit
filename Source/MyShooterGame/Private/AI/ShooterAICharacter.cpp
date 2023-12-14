// MyShooterGame


#include "AI/ShooterAICharacter.h"
#include "AI/ShooterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ShooterAIWeaponComponent.h"
#include "BrainComponent.h"
#include "UI/Shooter_Health_Bar_AI_Widget.h"
#include "Components/ShooterHealthComponent.h"

AShooterAICharacter::AShooterAICharacter(const FObjectInitializer& ObjInit)
	:Super(ObjInit.SetDefaultSubobjectClass<UShooterAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AShooterAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

	Health_Widget_Component = CreateDefaultSubobject<UWidgetComponent>("Health_Widget_Component");
	Health_Widget_Component->SetupAttachment(GetRootComponent());
	Health_Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
	Health_Widget_Component->SetDrawAtDesiredSize(true);
}

void AShooterAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Update_Health_Widget_Visibility();
}

void AShooterAICharacter::Update_Health_Widget_Visibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
	{
		return;
	}

	const auto Player_Location = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(Player_Location, GetActorLocation());
	Health_Widget_Component->SetVisibility(Distance < Health_Visible_Distance, true);

}


void AShooterAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(Health_Widget_Component);
}

void AShooterAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto ShooterController = Cast<AAIController>(Controller);
	if (ShooterController && ShooterController->BrainComponent)
	{
		ShooterController->BrainComponent->Cleanup();
	}
}



void AShooterAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);

	const auto Health_Bar_Widget = Cast<UShooter_Health_Bar_AI_Widget>(Health_Widget_Component->GetUserWidgetObject());

	if (!Health_Bar_Widget)
	{
		return;
	}

	Health_Bar_Widget->Set_Health_Percent(ShooterHealthComponent->GetHealthPercent());
}

