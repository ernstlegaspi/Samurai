#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusClass.generated.h"

UCLASS()
class SAMURAI_API UPlayerStatusClass : public UUserWidget {
	GENERATED_BODY()

public:
	void SetHealth(float CurrentHealth);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;
	
};
