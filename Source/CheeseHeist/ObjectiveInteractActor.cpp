// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveInteractActor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ObjectiveHandler.h"


AObjectiveInteractActor::AObjectiveInteractActor() {
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Box"));
	BoxComponent->InitBoxExtent(FVector(10, 10, 10));
	BoxComponent->SetCollisionProfileName("BlockAll");
	BoxComponent->SetupAttachment(RootComponent);

	bIsLocked = true;
}

void AObjectiveInteractActor::Interact() {

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

bool AObjectiveInteractActor::GetLockStatus() {

	return bIsLocked;

}

void AObjectiveInteractActor::Unlock() {
	bIsLocked = false;
}

void AObjectiveInteractActor::Lock() {
	bIsLocked = true;
}