#include "PlayerStatusClass.h"
#include "Components/ProgressBar.h"

void UPlayerStatusClass::SetHealth(float CurrentHealth) {
	HealthBar->SetPercent(CurrentHealth);
}