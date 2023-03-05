#include "EnemyAttackState.h"
#include "EnemySamurai.h"

void UEnemyAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(AEnemySamurai* ESamurai = (AEnemySamurai*)MeshComp->GetOwner()) ESamurai->ActivateCollision();
}

void UEnemyAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(AEnemySamurai* ESamurai = (AEnemySamurai*)MeshComp->GetOwner()) ESamurai->DeactivateCollision();
}