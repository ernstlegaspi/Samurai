#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "EnemySamuraiController.generated.h"

class UAnimMontage;

UCLASS()
class SAMURAI_API AEnemySamuraiController : public AAIController {
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class APawn* Samurai;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Attack;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Idle;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Run;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Stance;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_StanceForward;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Walk;

	UPROPERTY()
	class UNavigationSystemV1* NavLoc;

	UPROPERTY()
	class AEnemySamurai* ESamurai;

	FNavLocation Loc;
	FVector PawnLoc;

	float FollowDistance, IdleTimer;
	bool bOnGround, bPlayStanceOnce, bIdleDone;

	bool MPlaying(UAnimMontage* AM);
	float Dist(FVector D1, FVector D2);
	void HandleAnimation(UAnimMontage* AM);
	void PlayAnim(UAnimMontage* AM);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
