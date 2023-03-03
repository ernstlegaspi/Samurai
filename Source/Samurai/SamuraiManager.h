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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Slash1;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Idle;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Walk;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Run;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* SamuraiMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* Slash1Action;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* RunAction;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* SamuraiTrigger;

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	UPROPERTY()
	UAnimMontage* PrevMontage;

	bool MIsPlaying(class UAnimMontage* AM);
	void HandleAnimation(class UAnimMontage* AM);
	void Move(const FInputActionValue& Value);
	void SlashStart();
	void Run();
	void RunCompleted();

	float Slash1Time;
	bool bShiftPressed, bSlashing;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
