#include "EnemySamurai.h"
#include "EnemyStatusClass.h"
#include "SamuraiManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"



#include "Blueprint/AIBlueprintHelperLibrary.h"


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
}

void AEnemySamurai::BeginPlay() {
	Super::BeginPlay();

	AnimInstance = GetMesh()->GetAnimInstance();
	Character = GetCharacterMovement();
	Samurai = (ASamuraiManager*)UGameplayStatics::GetActorOfClass(GetWorld(), ASamuraiManager::StaticClass());
	EnemyStatus->bHiddenInGame = true;
	EnemyStatusClass = Cast<UEnemyStatusClass>(CreateWidget(GetWorld(), EnemyStatusWidget));
	EnemyStatus->SetWidget(EnemyStatusClass);
	EnemyCurrentHealth = 1.f;
}

void AEnemySamurai::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	EnemyStatus->bHiddenInGame = !(FVector::Dist(Samurai->GetActorLocation(), GetActorLocation()) <= 1000.f);
	if(EnemyCurrentHealth <= 0.f) Destroy();

	// UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Samurai->GetActorLocation());
}

void AEnemySamurai::EnemyEnterOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor != this) {
		EnemyCurrentHealth -= .35f;
		EnemyStatusClass->SetHealth(EnemyCurrentHealth);
	}
}

void AEnemySamurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}