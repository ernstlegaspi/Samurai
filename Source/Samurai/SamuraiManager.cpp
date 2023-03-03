#include "SamuraiManager.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

ASamuraiManager::ASamuraiManager() {
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SamuraiTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Samurai Trigger"));
	SamuraiTrigger->InitCapsuleSize(80.f, 50.f);
	SamuraiTrigger->SetupAttachment(RootComponent);
}

void ASamuraiManager::BeginPlay() {
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(SamuraiMappingContext, 0);
		}
	}

	AnimInstance = GetMesh()->GetAnimInstance();
}

void ASamuraiManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(!bSlashing) {
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
}

bool ASamuraiManager::MIsPlaying(UAnimMontage* AM) {
	return AnimInstance->Montage_IsPlaying(AM);
}

void ASamuraiManager::HandleAnimation(UAnimMontage* AM) {
	if(MIsPlaying(PrevMontage) && PrevMontage != AM) AnimInstance->Montage_Stop(0, PrevMontage);
	if(!MIsPlaying(AM)) AnimInstance->Montage_Play(AM);

	PrevMontage = AM;
}

void ASamuraiManager::Move(const FInputActionValue& Value) {
	const FVector2D Dir = Value.Get<FVector2D>();

	if(Controller != nullptr) {
		FRotator SamuraiRotation = GetControlRotation();
		FRotator NewYawRotation(0, SamuraiRotation.Yaw, 0);

		FVector Forward = FRotationMatrix(NewYawRotation).GetUnitAxis(EAxis::X);
		FVector Right = FRotationMatrix(NewYawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, Dir.Y);
		AddMovementInput(Right, Dir.X);
	}
}

void ASamuraiManager::SlashManager(UAnimMontage* AM, UAnimMontage* OtherAM) {
	if(!MIsPlaying(AM) && !MIsPlaying(OtherAM)) {
		if(MIsPlaying(PrevMontage) && PrevMontage != AM) AnimInstance->Montage_Stop(0, PrevMontage);
		AnimInstance->Montage_Play(AM);
		PrevMontage = AM;
		bSlashing = true;
		CurrentSlash = AM;
	}
}

void ASamuraiManager::Slash1Start() {
	SlashManager(AM_Slash1, AM_Slash2);
}

void ASamuraiManager::Slash2Start() {
	SlashManager(AM_Slash2, AM_Slash1);
}

void ASamuraiManager::Run() {
	bShiftPressed = true;
}

void ASamuraiManager::RunCompleted() {
	bShiftPressed = false;
}

void ASamuraiManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASamuraiManager::Move);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ASamuraiManager::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ASamuraiManager::RunCompleted);
		EnhancedInputComponent->BindAction(Slash1Action, ETriggerEvent::Started, this, &ASamuraiManager::Slash1Start);
		EnhancedInputComponent->BindAction(Slash2Action, ETriggerEvent::Started, this, &ASamuraiManager::Slash2Start);
	}
}