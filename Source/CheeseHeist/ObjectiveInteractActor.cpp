// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveInteractActor.h"
#include "ObjectiveHandler.h"
#include "Kismet/GameplayStatics.h"

void AObjectiveInteractActor::OnInteract(AActor* ObjectToUnlock) {

	if (bIsCompleted) {
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Completed"));

		return;
	}

	if (!IsObjectOpen) {
		if (AnimOpenObject != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Opening"));

			return;
		}
	}

	if (GetLockStatus()) {
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Locked"));

		return;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Unlocked"));
	}

	if (ObjectToUnlock != nullptr) { // To be deleted???
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted to unlock Object | Unlocked"));
	}

	UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Completed"));

	bIsCompleted = true; // DEBUG

}

void AObjectiveInteractActor::SetComplete(bool Status) {
	bIsCompleted = Status;
}

bool AObjectiveInteractActor::CheckForCompletion() {
	return bIsCompleted;
}

void AObjectiveInteractActor::OpenObject() {
	return;
}