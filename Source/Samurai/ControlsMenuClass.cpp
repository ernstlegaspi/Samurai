#include "ControlsMenuClass.h"
#include "Components/Button.h"

void UControlsMenuClass::NativeConstruct() {
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &UControlsMenuClass::BackButtonClicked);
}

void UControlsMenuClass::BackButtonClicked() {
	bBackButtonClicked = true;
}
