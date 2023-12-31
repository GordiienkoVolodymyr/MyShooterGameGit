// MyShooterGame


#include "Components/ShooterHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include <MyShooterGame/ShooterGameModeBase.h>

UShooterHealthComponent::UShooterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UShooterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UShooterHealthComponent::OnTakeAnydamageHandle);
	}
}


void UShooterHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UShooterHealthComponent::OnTakeAnydamageHandle(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
	{
		return;
	}
	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UShooterHealthComponent::HealUpdate,
			HealUpdateTime, true, HealDelay);
	}
	PlayCameraShake();
}

void UShooterHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	
	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UShooterHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHelth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HelthDelta = NextHelth - Health;

	Health = NextHelth;
	OnHealthChanged.Broadcast(Health, HelthDelta);
}


bool UShooterHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull())
	{
		return false;
	}
	SetHealth(Health + HealthAmount);
	return true;
}

bool UShooterHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UShooterHealthComponent::PlayCameraShake()
{
	if (IsDead())
	{
		return;
	}

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player)
	{
		return;
	}

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager)
	{
		return;
	}
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UShooterHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld())
	{
		return;
	}
	const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}
	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);

}
