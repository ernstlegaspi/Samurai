#include "SamuraiManager.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASamuraiManager::ASamuraiManager() {
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SamuraiTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Samurai Trigger"));
	SamuraiTrigger->InitCapsuleSize(80.f, 50.f);
	SamuraiTrigger->SetupAttachment(RootComponent);

	WeaponTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Trigger"));
	WeaponTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	WeaponTrigger->SetGenerateOverlapEvents(true);
	WeaponTrigger->SetupAttachment(GetMesh(), FName("WeaponTrigger"));
}

void ASamuraiManager::BeginPlay() {
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(SamuraiMappingContext, 0);
		}
	}

	AnimInstance = GetMesh()->GetAnimInstance();
	WeaponTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASamuraiManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(!bDead) {
		if(GetCharacterMovement()->IsMovingOnGround()) {
			if(bControlPressed) {
				// HandleAnimation(AM_Roll);
				AnimInstance->Montage_Play(AM_Roll);

				if(!AnimInstance->Montage_IsPlaying(AM_Roll)) bControlPressed = true;

			}
			else if(!bSlashing) {
				if(GetVelocity() != FVector(0, 0, 0)) {
					if(bShiftPressed) {
						HandleAnimation(AM_Run);
						GetCharacterMovement()->MaxWalkSpeed = 500.f;
					}
					else {
						HandleAnimation(AM_Walk);
						GetCharacterMovement()->MaxWalkSpeed = 150.f;
					}
				}
				else HandleAnimation(AM_Idle);
			}
			else {
				if(!MIsPlaying(CurrentSlash)) bSlashing = false;
			}

			bJumping = false;
		}
		else {
			HandleAnimation(AM_Jump);
			bJumping = true;
		}
	}
	else {
		if(!bDeathAnimPlayOnce) {
			AnimInstance->Montage_Play(AM_Death);
			bDeathAnimPlayOnce = true;
		}

		if(AnimInstance->Montage_GetIsStopped(AM_Death)) AnimInstance->Montage_JumpToSection("DeathEnd");
	}
}

bool ASamuraiManager::MIsPlaying(UAnimMontage* AM) {
	return AnimInstance->Montage_IsPlaying(AM);
}

void ASamuraiManager::HandleAnimation(UAnimMontage* AM) {
	if(MIsPlaying(PrevMontage) && PrevMontage != AM) AnimInstance->Montage_Stop(0.3f, PrevMontage);
	if(!MIsPlaying(AM)) AnimInstance->Montage_Play(AM);

	PrevMontage = AM;
}

void ASamuraiManager::Move(const FInputActionValue& Value) {
	const FVector2D Dir = Value.Get<FVector2D>();

	if(Controller != nullptr && !bJumping && !bDead) {
		FRotator SamuraiRotation = GetControlRotation();
		FRotator NewYawRotation(0, SamuraiRotation.Yaw, 0);

		FVector Forward = FRotationMatrix(NewYawRotation).GetUnitAxis(EAxis::X);
		FVector Right = FRotationMatrix(NewYawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, Dir.Y);
		AddMovementInput(Right, Dir.X);
	}
}

void ASamuraiManager::MouseLook(const FInputActionValue& Value) {
	const FVector2D LookAxis = Value.Get<FVector2D>();

	if(Controller != nullptr) {
		AddControllerYawInput(-LookAxis.X);
		AddControllerPitchInput(LookAxis.Y);
	}
}

void ASamuraiManager::SlashManager(UAnimMontage* AM, UAnimMontage* OtherAM) {
	if(!MIsPlaying(AM) && !MIsPlaying(OtherAM) && !bJumping && !bDead) {
		if(MIsPlaying(PrevMontage) && PrevMontage != AM) AnimInstance->Montage_Stop(0, PrevMontage);
		AnimInstance->Montage_Play(AM);
		PrevMontage = AM;
		bSlashing = true;
		CurrentSlash = AM;
	}
}

void ASamuraiManager::Slash1Start() {
	SlashManager(AM_Slash1, AM_Slash2);
	bLeftClick = true;
}

void ASamuraiManager::Slash2Start() {
	SlashManager(AM_Slash2, AM_Slash1);
	bLeftClick = false;
}

void ASamuraiManager::Roll() {
	if(!bJumping && !bDead) {
		bControlPressed = true;
		// GetMesh()->AddImpulse(GetActorForwardVector() * 150.f * GetMesh()->GetMass());
	}
}

void ASamuraiManager::Run() {
	if(!bJumping && !bDead) bShiftPressed = true;
}

void ASamuraiManager::RunCompleted() {
	if(!bJumping && !bDead) bShiftPressed = false;
}

void ASamuraiManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASamuraiManager::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ASamuraiManager::MouseLook);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &ASamuraiManager::Roll);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ASamuraiManager::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ASamuraiManager::RunCompleted);
		EnhancedInputComponent->BindAction(Slash1Action, ETriggerEvent::Started, this, &ASamuraiManager::Slash1Start);
		EnhancedInputComponent->BindAction(Slash2Action, ETriggerEvent::Started, this, &ASamuraiManager::Slash2Start);
	}
}