// MyShooterGame


#include "Animations/ShooterAnimNotify.h"


void UShooterAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifySignature.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}