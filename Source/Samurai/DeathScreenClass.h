#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreenClass.generated.h"

UCLASS()
class SAMURAI_API UDeathScreenClass : public UUserWidget {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerStatusText;

};
