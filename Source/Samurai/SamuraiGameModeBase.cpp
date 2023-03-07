#include "SamuraiGameModeBase.h"
#include "DeathScreenClass.h"
#include "PlayerStatusClass.h"
#include "SamuraiManager.h"
#include "Kismet/GameplayStatics.h"

ASamuraiGameModeBase::ASamuraiGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ASamuraiGameModeBase::BeginPlay() {
	Super::BeginPlay();

	if(PlayerStatusWidget) {
		PlayerStatusClass = CreateWidget<UPlayerStatusClass>(GetWorld(), PlayerStatusWidget);
		PlayerStatusClass->AddToViewport();
	}

	CurrentHealth = 1.f;
	Samurai = (ASamuraiManager*)UGameplayStatics::GetActorOfClass(this, ASamuraiManager::StaticClass());
}

void ASamuraiGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(bHit) {
		CurrentHealth -= .15f;
		PlayerStatusClass->SetHealth(CurrentHealth);
		bHit = false;

		if(CurrentHealth <= 0) {
			Samurai->bDead = true;
			PlayerStatusClass->RemoveFromParent();
			PlayerStatusClass = nullptr;
			DeathScreenClass = CreateWidget<UDeathScreenClass>(GetWorld(), DeathScreenWidget);
			DeathScreenClass->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("Deaddd"));
		}
	}
}