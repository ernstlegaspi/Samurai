#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SamuraiAttackState.generated.h"

UCLASS()
class SAMURAI_API USamuraiAttackState : public UAnimNotifyState{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* HitComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* HitComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
