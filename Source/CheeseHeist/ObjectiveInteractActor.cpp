// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveInteractActor.h"
#include "Kismet/GameplayStatics.h"

void AObjectiveInteractActor::OnInteract(AActor* ObjectToUnlock) {

	if (GetLockStatus()) {
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Locked"));

		return;
	}

	if (ObjectToUnlock != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted to unlock Object | Unlocked"));
	}

	UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Unlocked"));

}

void AObjectiveInteractActor::OnUnlock() {
	return;
}