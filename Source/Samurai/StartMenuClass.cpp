#include "StartMenuClass.h"
#include "Components/Button.h"

void UStartMenuClass::NativeConstruct() {
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UStartMenuClass::StartButtonClicked);
	ControlsButton->OnClicked.AddDynamic(this, &UStartMenuClass::ControlsButtonClicked);
}

void UStartMenuClass::StartButtonClicked() {
	bStartClicked = true;
}

void UStartMenuClass::ControlsButtonClicked() {
	bControlsClicked = true;
}