// MyShooterGame


#include "Components/ShooteCharacterMovementComponent.h"
#include "Player/ShooterCharacter.h"

float UShooteCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AShooterCharacter* Player = Cast<AShooterCharacter>(GetOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
