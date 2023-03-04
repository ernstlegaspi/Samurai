#include "SamuraiAttackState.h"
#include "SamuraiManager.h"
#include "Components/BoxComponent.h"

void USamuraiAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Samurai = (ASamuraiManager*)MeshComp->GetOwner();
	Samurai->WeaponTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void USamuraiAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	Samurai->WeaponTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}