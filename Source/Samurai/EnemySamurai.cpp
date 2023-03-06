#include "EnemySamurai.h"
#include "EnemyStatusClass.h"
#include "SamuraiManager.h"
#include "SamuraiGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

AEnemySamurai::AEnemySamurai() {
	PrimaryActorTick.bCanEverTick = true;

	EnemyTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Enemy Trigger"));
	EnemyTrigger->InitCapsuleSize(50.f, 80.f);
	EnemyTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	EnemyTrigger->SetGenerateOverlapEvents(true);
	EnemyTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemySamurai::EnemyEnterOverlap);
	EnemyTrigger->SetupAttachment(RootComponent);

	EnemyStatus = CreateDefaultSubobject<UWidgetComponent>(TEXT("Enemy Status"));
	EnemyStatus->SetupAttachment(RootComponent);

	WeaponTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Trigger"));
	WeaponTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemySamurai::WeaponEnterOverlap);
	WeaponTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	WeaponTrigger->SetGenerateOverlapEvents(true);
	WeaponTrigger->SetupAttachment(GetMesh(), FName("WeaponTrigger"));
}

void AEnemySamurai::BeginPlay() {
	Super::BeginPlay();

	Character = GetCharacterMovement();
	AnimInstance = GetMesh()->GetAnimInstance();

	Samurai = (ASamuraiManager*)UGameplayStatics::GetActorOfClass(GetWorld(), ASamuraiManager::StaticClass());
	SamuraiGMB = (ASamuraiGameModeBase*)UGameplayStatics::GetActorOfClass(GetWorld(), ASamuraiGameModeBase::StaticClass());
	EnemyStatus->bHiddenInGame = true;
	EnemyStatusClass = Cast<UEnemyStatusClass>(CreateWidget(GetWorld(), EnemyStatusWidget));
	EnemyStatus->SetWidget(EnemyStatusClass);

	EnemyCurrentHealth = 1.f;
	HitCount = 0.f;

	WeaponTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemySamurai::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	EnemyStatus->bHiddenInGame = !(FVector::Dist(Samurai->GetActorLocation(), GetActorLocation()) <= 1000.f);

	if(EnemyCurrentHealth <= 0.f) {
		Destroy();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Death, GetActorLocation());
	}
	
	if(bGotHit) {
		if((HitCount == 1 && Samurai->AttackCount == 1) && bGotHit) {
			AnimStage = Samurai->bLeftClick ? EAnimationStage::BodyHit : EAnimationStage::SideHit;
		}
		else {
			if(((HitCount == 1 && Samurai->AttackCount == 2) || HitCount == 2) && bGotHit) {
				AnimStage = Samurai->bLeftClick ? EAnimationStage::HeadHit : EAnimationStage::KidneyHit;
			}
		}
	}

	if(bInHeadHitAnim && !MPlaying(Samurai->bLeftClick ? AM_HeadHit : AM_KidneyHit)) {
		bGotHit = false;
		bInHeadHitAnim = false;

		HitCount = 0;
		AnimStage = EAnimationStage::StanceForward;
	}

	switch(AnimStage) {
		case EAnimationStage::Idle: HandleAnimation(AM_Idle); break;
		case EAnimationStage::Run: HandleAnimation(AM_Run); break;
		case EAnimationStage::StanceForward: HandleAnimation(AM_StanceForward); break;
		case EAnimationStage::Walk: HandleAnimation(AM_Walk); break;
		case EAnimationStage::BodyHit: HandleAnimation(AM_BodyHit); break;
		case EAnimationStage::SideHit: HandleAnimation(AM_SideHit); break;
		case EAnimationStage::Attack:
			if(!bAttackPlayOnce) {
				bAttackPlayOnce = true;
				PlayAnim(AM_Attack);
			}

			if(!MPlaying(AM_Attack)) {
				bAttackPlayOnce = false;
				AnimStage = EAnimationStage::StanceForward;
			}
			break;
		case EAnimationStage::Stance:
			if(!bStancePlayOnce) {
				PlayAnim(AM_Stance);
				bStancePlayOnce = true;
			}

			if(bStancePlayOnce && !MPlaying(AM_Stance)) {
				bStanceFinished = true;
				bStancePlayOnce = false;
			}
			break;
		case EAnimationStage::HeadHit:
		case EAnimationStage::KidneyHit:
			AnimInstance->Montage_Stop(.4f, AnimStage == EAnimationStage::HeadHit ? AM_BodyHit : AM_SideHit);
			HandleAnimation(AnimStage == EAnimationStage::HeadHit ? AM_HeadHit : AM_KidneyHit);
			bInHeadHitAnim = true;
			break;
	}
}

bool AEnemySamurai::MPlaying(UAnimMontage* AM) {
	return AnimInstance->Montage_IsPlaying(AM);
}

void AEnemySamurai::HandleAnimation(UAnimMontage* AM) {
	if(!MPlaying(AM)) PlayAnim(AM);
}

void AEnemySamurai::PlayAnim(UAnimMontage* AM) {
	AnimInstance->Montage_Play(AM);
}

void AEnemySamurai::ActivateCollision() {
	WeaponTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AEnemySamurai::DeactivateCollision() {
	WeaponTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemySamurai::EnemyEnterOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor->GetName().Contains("SamuraiManager")) {
		EnemyCurrentHealth -= .25f;
		EnemyStatusClass->SetHealth(EnemyCurrentHealth);
		bGotHit = true;
		HitCount++;
	}
}

void AEnemySamurai::WeaponEnterOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor != this) SamuraiGMB->bHit = true;
}

void AEnemySamurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}