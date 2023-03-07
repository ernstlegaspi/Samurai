#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuClass.generated.h"


UCLASS()
class SAMURAI_API UStartMenuClass : public UUserWidget {
	GENERATED_BODY()
	
public:
	bool bStartClicked, bControlsClicked;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ControlsButton;

	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void ControlsButtonClicked();

};
