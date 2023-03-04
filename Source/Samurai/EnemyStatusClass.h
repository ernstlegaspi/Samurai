#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyStatusClass.generated.h"


UCLASS()
class SAMURAI_API UEnemyStatusClass : public UUserWidget {
	GENERATED_BODY()

public:
	void SetHealth(float CurrentHealth);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* EnemyHealth;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* EnemyName;

};
