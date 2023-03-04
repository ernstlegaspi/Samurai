#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySamurai.h"
#include "EnemySamuraiController.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SAMURAI_API AEnemySpawner : public AActor {
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemySamurai> EnemySamurai;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemySamuraiController> EnemySamuraiAI;

	UPROPERTY()
	class AEnemySamurai* Enemy;

	UPROPERTY()
	class AEnemySamuraiController* EnemyAI;

	int SpawnCount;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
