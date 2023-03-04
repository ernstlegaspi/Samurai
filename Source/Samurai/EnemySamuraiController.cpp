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
	ESamurai = (AEnemySamurai*)UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySamurai::StaticClass());
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
		if(!bPlayStanceOnce) {
			StopMovement();
			PlayAnim(AM_Stance);
			bPlayStanceOnce = true;
			FollowDistance = 1000.f;
		}

		if(Dist(Samurai->GetActorLocation(), PawnLoc) > 1000.f) {
			HandleAnimation(AM_Run);
			MoveToLocation(Samurai->GetActorLocation());
			ESamurai->Character->MaxWalkSpeed = 350.f;
			bIdleDone = false;
		}
		else {
			ESamurai->Character->MaxWalkSpeed = 150.f;

			if(!MPlaying(AM_Stance)) {
				HandleAnimation(AM_StanceForward);
				MoveToLocation(Samurai->GetActorLocation());
			}
			else {
				GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), Samurai->GetActorLocation()));
			}
		}
	}
	else {
		bPlayStanceOnce = false;
		FollowDistance = 0;

		if(IdleTimer <= 0) {
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

			if(!MPlaying(AM_Walk)) PlayAnim(AM_Walk);
		}
		else {
			IdleTimer -= DeltaTime;
			StopMovement();
			HandleAnimation(AM_Idle);
			bIdleDone = false;
		}
	}
}

bool AEnemySamuraiController::MPlaying(UAnimMontage* AM) {
	return ESamurai->AnimInstance->Montage_IsPlaying(AM);
}

void AEnemySamuraiController::HandleAnimation(UAnimMontage* AM) {
	if(!MPlaying(AM)) PlayAnim(AM);
}

void AEnemySamuraiController::PlayAnim(UAnimMontage* AM) {
	ESamurai->AnimInstance->Montage_Play(AM);
}

float AEnemySamuraiController::Dist(FVector D1, FVector D2) {
	return FVector::Dist(D1, D2);
}