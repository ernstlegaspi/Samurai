#include "EnemyStatusClass.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UEnemyStatusClass::NativeConstruct() {
	Super::NativeConstruct();

	EnemyName->SetText(FText::FromString("Oni Samurai"));
}

void UEnemyStatusClass::SetHealth(float CurrentHealth) {
	EnemyHealth->SetPercent(CurrentHealth);
}