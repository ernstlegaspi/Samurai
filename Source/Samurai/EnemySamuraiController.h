#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemySamuraiController.generated.h"

UCLASS()
class SAMURAI_API AEnemySamuraiController : public AAIController {
	GENERATED_BODY()

protected:
	AEnemySamuraiController();

	UPROPERTY()
	class ASamuraiManager* Samurai;

	UPROPERTY()
	class UNavigationSystemV1* NavLoc;

	UPROPERTY()
	class AEnemySamurai* ESamurai;

	FNavLocation Loc;
	FVector PawnLoc;

	float FollowDistance, IdleTimer;
	bool bOnGround, bIdleDone;

	float Dist(FVector D1, FVector D2);
	void LookTo();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
