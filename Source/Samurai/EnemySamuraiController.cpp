#include "EnemySamuraiController.h"
#include "EnemySamurai.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"

void AEnemySamuraiController::BeginPlay() {
	Super::BeginPlay();

	Samurai = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ESamurai = Cast<AEnemySamurai>(GetPawn());
	NavLoc = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	bOnGround = NavLoc->GetRandomReachablePointInRadius(PawnLoc, 500.f, Loc);
	MoveToLocation(Loc.Location);
	FollowDistance = 0;
	IdleTimer = 0;
	bIdleDone = true;
}

void AEnemySamuraiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	PawnLoc = GetPawn()->GetActorLocation();

	if(Dist(Samurai->GetActorLocation(), PawnLoc) <= (1000.f + FollowDistance)) {
		if(!ESamurai->bGotHit) {
			if(ESamurai->bStanceFinished) {
				if(ESamurai->AnimStage != EAnimationStage::Attack) {
					if(Dist(Samurai->GetActorLocation(), PawnLoc) > 1000.f) {
						MoveToLocation(Samurai->GetActorLocation());
						ESamurai->Character->MaxWalkSpeed = 350.f;
						ESamurai->AnimStage = EAnimationStage::Run;
					}
					else if(Dist(Samurai->GetActorLocation(), PawnLoc) <= 200.f) {
						StopMovement();
						GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(PawnLoc, Samurai->GetActorLocation()));
						ESamurai->AnimStage = EAnimationStage::Attack;
					}
					else {
						ESamurai->Character->MaxWalkSpeed = 150.f;
						ESamurai->AnimStage = EAnimationStage::StanceForward;
						MoveToLocation(Samurai->GetActorLocation());
					}
				}

				IdleTimer = 3.f;
			}
			else {
				StopMovement();
				ESamurai->AnimStage = EAnimationStage::Stance;
				GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(PawnLoc, Samurai->GetActorLocation()));
				FollowDistance = 1000.f;
			}
		}
	}
	else {
		FollowDistance = 0;
		ESamurai->bStanceFinished = false;

		if(IdleTimer <= 0) {
			ESamurai->Character->MaxWalkSpeed = 200.f;
			ESamurai->AnimStage = EAnimationStage::Walk;

			if(!bIdleDone) {
				bOnGround = NavLoc->GetRandomReachablePointInRadius(PawnLoc, 1500.f, Loc);
				MoveToLocation(Loc.Location);
				bIdleDone = true;
			}

			if(Dist(Loc.Location, PawnLoc) <= 300.f) {
				bOnGround = NavLoc->GetRandomReachablePointInRadius(PawnLoc, 1500.f, Loc);
				MoveToLocation(Loc.Location);
				IdleTimer = 3.f;
			}
		}
		else {
			IdleTimer -= DeltaTime;
			StopMovement();
			ESamurai->AnimStage = EAnimationStage::Idle;
			bIdleDone = false;
		}
	}
}

float AEnemySamuraiController::Dist(FVector D1, FVector D2) {
	return FVector::Dist(D1, D2);
}