// MyShooterGame


#include "Player/ShooterPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/ShooterWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

AShooterPlayerCharacter::AShooterPlayerCharacter(const FObjectInitializer& ObjInit) :
	Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 80.0f, 80.f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(SpringArmComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AShooterPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AShooterPlayerCharacter::OnComponentBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AShooterPlayerCharacter::OnComponentEndOverlap);
}

void AShooterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight/Left", this, &AShooterPlayerCharacter::MoveRightLeft);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookAround", this, &AShooterPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AShooterPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AShooterPlayerCharacter::OnStopRun);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UShooterWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UShooterWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UShooterWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UShooterWeaponComponent::Reload);
	DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &UShooterWeaponComponent::Zoom, true);
	PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &UShooterWeaponComponent::Zoom, false);
}

bool AShooterPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void AShooterPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	if (Amount == 0.0f)
	{
		return;
	}
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AShooterPlayerCharacter::MoveRightLeft(float Amount)
{
	if (Amount == 0.0f)
	{
		return;
	}
	AddMovementInput(GetActorRightVector(), Amount);
}

void AShooterPlayerCharacter::OnStartRun()
{
	WantsToRun = true;
}

void AShooterPlayerCharacter::OnStopRun()
{
	WantsToRun = false;
}

void AShooterPlayerCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ChechCameraOverlap();
}

void AShooterPlayerCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ChechCameraOverlap();
}

void AShooterPlayerCharacter::ChechCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true, MeshChildren);

	for (auto MeshChild : MeshChildren)
	{
		const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
		if (MeshChildGeometry)
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}

void AShooterPlayerCharacter::OnDeath()
{
	//PlayAnimMontage(DeathAnimMontage);
	Super::OnDeath();
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}