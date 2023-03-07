#include "SamuraiGameModeBase.h"
#include "ControlsMenuClass.h"
#include "DeathScreenClass.h"
#include "PlayerStatusClass.h"
#include "StartMenuClass.h"
#include "SamuraiManager.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

ASamuraiGameModeBase::ASamuraiGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ASamuraiGameModeBase::BeginPlay() {
	Super::BeginPlay();

	if(StartMenuWidget) {
		StartMenuClass = CreateWidget<UStartMenuClass>(GetWorld(), StartMenuWidget);
		StartMenuClass->AddToViewport();
	}

	CurrentHealth = 1.f;
	PlayerStatusClass = nullptr;
	ControlsMenuClass = nullptr;
	Samurai = (ASamuraiManager*)UGameplayStatics::GetActorOfClass(this, ASamuraiManager::StaticClass());
}

void ASamuraiGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(StartMenuClass != nullptr) {
		if(StartMenuClass->bStartClicked) {
			Stage = 1;
			StartMenuClass->bStartClicked = false;
			StartMenuClass->RemoveFromParent();
			StartMenuClass = nullptr;
			PlayerStatusClass = CreateWidget<UPlayerStatusClass>(GetWorld(), PlayerStatusWidget);
			PlayerStatusClass->AddToViewport();
		}
		else {
			if(StartMenuClass->bControlsClicked) {
				StartMenuClass->bControlsClicked = false;
				StartMenuClass->RemoveFromParent();
				ControlsMenuClass = CreateWidget<UControlsMenuClass>(GetWorld(), ControlsMenuWidget);
				ControlsMenuClass->AddToViewport();
			}
		}
	}

	if(ControlsMenuClass != nullptr) {
		if(ControlsMenuClass->bBackButtonClicked) {
			ControlsMenuClass->RemoveFromParent();
			ControlsMenuClass->bBackButtonClicked = false;
			ControlsMenuClass = nullptr;
			StartMenuClass->bControlsClicked = false;
			StartMenuClass->AddToViewport();
		}
	}

	if(PlayerStatusClass != nullptr && bHit && !bPlayerWon) {
		CurrentHealth -= .15f;
		PlayerStatusClass->SetHealth(CurrentHealth);
		bHit = false;

		if(CurrentHealth <= 0) {
			Samurai->bDead = true;
			PlayerStatusClass->RemoveFromParent();
			PlayerStatusClass = nullptr;
			GameStatusClass = CreateWidget<UDeathScreenClass>(GetWorld(), GameStatusWidget);
			GameStatusClass->AddToViewport();
			GameStatusClass->PlayerStatusText->SetText(FText::FromString("You died!"));
		}
	}
	else {
		if(bPlayerWon && !bShowOnce) {
			PlayerStatusClass->RemoveFromParent();
			PlayerStatusClass = nullptr;
			GameStatusClass = CreateWidget<UDeathScreenClass>(GetWorld(), GameStatusWidget);
			GameStatusClass->AddToViewport();
			GameStatusClass->PlayerStatusText->SetText(FText::FromString("You won!"));
			bShowOnce = true;
		}
	}
}