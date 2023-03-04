#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay() {
	Super::BeginPlay();

	SpawnCount = 0;
}

void AEnemySpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(SpawnCount <= 1) {
		Enemy = GetWorld()->SpawnActor<AEnemySamurai>(EnemySamurai, GetActorTransform());
		EnemyAI = GetWorld()->SpawnActor<AEnemySamuraiController>(EnemySamuraiAI, GetActorTransform());
		EnemyAI->Possess(Enemy);
		SpawnCount++;
	}
}

