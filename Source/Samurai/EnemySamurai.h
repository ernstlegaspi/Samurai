#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySamurai.generated.h"

UCLASS()
class SAMURAI_API AEnemySamurai : public ACharacter {
	GENERATED_BODY()

public:
	AEnemySamurai();

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	UPROPERTY()
	class UCharacterMovementComponent* Character;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* EnemyTrigger;

	UFUNCTION()
	void EnemyEnterOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
