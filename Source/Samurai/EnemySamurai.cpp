#include "EnemySamurai.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemySamurai::AEnemySamurai() {
	PrimaryActorTick.bCanEverTick = true;

	EnemyTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Enemy Trigger"));
	EnemyTrigger->InitCapsuleSize(50.f, 80.f);
	EnemyTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	EnemyTrigger->SetGenerateOverlapEvents(true);
	EnemyTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemySamurai::EnemyEnterOverlap);
	EnemyTrigger->SetupAttachment(RootComponent);
}

void AEnemySamurai::BeginPlay() {
	Super::BeginPlay();

	AnimInstance = GetMesh()->GetAnimInstance();
	Character = GetCharacterMovement();
}

void AEnemySamurai::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AEnemySamurai::EnemyEnterOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Enemy Hit"));
}

void AEnemySamurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}