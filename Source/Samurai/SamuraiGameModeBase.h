#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavigationSystem.h"
#include "SamuraiGameModeBase.generated.h"

UCLASS()
class SAMURAI_API ASamuraiGameModeBase : public AGameModeBase {
	GENERATED_BODY()
	
public:
	bool bHit, bPlayerWon;
	short Stage;

protected:
	ASamuraiGameModeBase();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerStatusWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ControlsMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameStatusWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartMenuWidget;

	UPROPERTY()
	class UPlayerStatusClass* PlayerStatusClass;

	UPROPERTY()
	class UDeathScreenClass* GameStatusClass;

	UPROPERTY()
	class UStartMenuClass* StartMenuClass;

	UPROPERTY()
	class UControlsMenuClass* ControlsMenuClass;

	UPROPERTY()
	class ASamuraiManager* Samurai;

	bool bShowOnce;
	float CurrentHealth;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
