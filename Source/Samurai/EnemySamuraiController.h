#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "EnemySamuraiController.generated.h"

UCLASS()
class SAMURAI_API AEnemySamuraiController : public AAIController {
	GENERATED_BODY()

protected:
	UPROPERTY()
	class APawn* Samurai;

	UPROPERTY()
	class UNavigationSystemV1* NavLoc;

	UPROPERTY()
	class AEnemySamurai* ESamurai;

	FNavLocation Loc;
	FVector PawnLoc;

	float FollowDistance, IdleTimer;
	bool bOnGround, bIdleDone;

	float Dist(FVector D1, FVector D2);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
