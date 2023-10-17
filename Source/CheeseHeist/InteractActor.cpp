// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "CheeseHeistCharacter.h"
#include "RatCharacter.h"

// Sets default values
AInteractActor::AInteractActor() {
	PrimaryActorTick.bCanEverTick = false;

	IsLocked = true;

}

void AInteractActor::BeginPlay() {
	Super::BeginPlay();
	
}

void AInteractActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AInteractActor::ChangeLockStatus(bool Status) {

	IsLocked = Status;

}

bool AInteractActor::GetLockStatus() {

	return IsLocked;

}

void AInteractActor::OnInteract(AActor* ObjectToUnlock) { // Function must be overwritten

	return;

}

// Rat does not use raycasting to interact due its nature as a 3rd person character, therefore it is based on a bounding box

void AInteractActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	ARatCharacter* Rat = Cast<ARatCharacter>(OtherActor);

	if (Rat != nullptr) { // Add IsControlled

	}


}

void AInteractActor::OnOverlapEnd(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	ARatCharacter* Rat = Cast<ARatCharacter>(OtherActor);
	
	if (Rat != nullptr) { // Add IsControlled

	}

}