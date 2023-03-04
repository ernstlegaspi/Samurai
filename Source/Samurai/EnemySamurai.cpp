// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySamurai.h"

// Sets default values
AEnemySamurai::AEnemySamurai()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySamurai::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySamurai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemySamurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

