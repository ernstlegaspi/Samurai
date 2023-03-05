#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySamurai.generated.h"

UENUM(BlueprintType)
enum class EAnimationStage : uint8 {
	Attack = 0 UMETA(DisplayName = "ATTACK"),
	Idle = 1 UMETA(DisplayName = "IDLE"),
	Run = 2 UMETA(DisplayName = "RUN"),
	Stance = 3 UMETA(DisplayName = "STANCE"),
	StanceForward = 4 UMETA(DisplayName = "STANCEFORWARD"),
	Walk = 5 UMETA(DisplayName = "WALK"),
	HeadHit = 6 UMETA(DisplayName = "HEADHIT"),
	BodyHit = 7 UMETA(DisplayName = "BODYHIT"),
	KidneyHit = 8 UMETA(DisplayName = "KIDNEYHIT"),
	SideHit = 9 UMETA(DisplayName = "SIDEHIT")
};

UCLASS()
class SAMURAI_API AEnemySamurai : public ACharacter {
	GENERATED_BODY()

public:
	AEnemySamurai();

	UPROPERTY()
	class UCharacterMovementComponent* Character;

	UPROPERTY()
	EAnimationStage AnimStage;

	bool bStanceFinished, bGotHit;

	void ActivateCollision();
	void DeactivateCollision();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Attack;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Idle;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Run;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Stance;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_StanceForward;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Walk;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_BodyHit;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_HeadHit;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_SideHit;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_KidneyHit;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> EnemyStatusWidget;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* EnemyTrigger;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* WeaponTrigger;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* EnemyStatus;

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	UPROPERTY()
	class ASamuraiManager* Samurai;
	
	UPROPERTY()
	class UEnemyStatusClass* EnemyStatusClass;

	UPROPERTY()
	class ASamuraiGameModeBase* SamuraiGMB;

	UFUNCTION()
	void EnemyEnterOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void WeaponEnterOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bStancePlayOnce, bAttackPlayOnce, bInHeadHitAnim;
	float EnemyCurrentHealth;
	short HitCount;

	bool MPlaying(UAnimMontage* AM);
	void HandleAnimation(UAnimMontage* AM);
	void PlayAnim(UAnimMontage* AM);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
