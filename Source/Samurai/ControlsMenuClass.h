#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsMenuClass.generated.h"

UCLASS()
class SAMURAI_API UControlsMenuClass : public UUserWidget {
	GENERATED_BODY()
	
public:
	bool bBackButtonClicked;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UFUNCTION()
	void BackButtonClicked();

	virtual void NativeConstruct() override;

};
