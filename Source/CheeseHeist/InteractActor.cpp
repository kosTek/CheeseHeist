// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "CheeseHeistCharacter.h"
#include "RatCharacter.h"

// Sets default values
AInteractActor::AInteractActor() {
	PrimaryActorTick.bCanEverTick = false;

	bRatOnlyInteract = false;

	bIsLocked = true;

}

void AInteractActor::BeginPlay() {
	Super::BeginPlay();
	
}

void AInteractActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AInteractActor::ChangeLockStatus(bool Status) {

	bIsLocked = Status;

	if (!bIsLocked) {
		OnUnlock();
	}

}

bool AInteractActor::GetLockStatus() {

	return bIsLocked;

}

void AInteractActor::OnInteract(AActor* ObjectToUnlock) { // Function must be overwritten

	return;

}

bool AInteractActor::GetCanInteract() {
	return bRatOnlyInteract;
}

void AInteractActor::OnUnlock() {
	return;
}