#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SamuraiManager.generated.h"

class UAnimMontage;
class UInputAction;

UCLASS()
class SAMURAI_API ASamuraiManager : public ACharacter {
	GENERATED_BODY()

public:
	ASamuraiManager();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* WeaponTrigger;

	bool bLeftClick, bDead;
	short AttackCount;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Death;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Slash1;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Slash2;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Idle;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Jump;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Walk;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Roll;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Run;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* SamuraiMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere)
	UInputAction* RestartAction;
	
	UPROPERTY(EditAnywhere)
	UInputAction* QuitAction;

	UPROPERTY(EditAnywhere)
	UInputAction* Slash1Action;

	UPROPERTY(EditAnywhere)
	UInputAction* Slash2Action;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* RollAction;

	UPROPERTY(EditAnywhere)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere)
	UInputAction* MouseLookAction;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* SamuraiTrigger;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	UPROPERTY()
	UAnimMontage* PrevMontage;

	UPROPERTY()
	UAnimMontage* CurrentSlash;

	bool MIsPlaying(UAnimMontage* AM);
	void HandleAnimation(UAnimMontage* AM);
	void Move(const FInputActionValue& Value);
	void MouseLook(const FInputActionValue& Value);
	void SlashManager(UAnimMontage* AM, UAnimMontage* OtherAM);
	void Slash1Start();
	void Slash2Start();
	void Roll();
	void Run();
	void RunCompleted();
	void RestartGameAction();
	void QuitGameAction();

	float Slash1Time;
	bool bControlPressed, bShiftPressed, bSlashing, bJumping, bDeathAnimPlayOnce;

public:	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
