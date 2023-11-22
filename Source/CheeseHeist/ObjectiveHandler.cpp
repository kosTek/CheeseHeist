// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveHandler.h"
#include "ObjectiveInteractActor.h"
#include "Objective.h"

// Sets default values
AObjectiveHandler::AObjectiveHandler() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectiveHandler::BeginPlay() {
	Super::BeginPlay();

	GenerateSeed();

	UE_LOG(LogTemp, Warning, TEXT("[Objectives] Seed: %i"), Seed.GetCurrentSeed())

	for (int i = 0; i < Objectives.Num(); i++) {
		if (Objectives[i] == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("[Objectives] Objective #%i NULLPTR"), i);
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("[Objectives] Processing objective #%i"), i);

		int32 SelectedSpawn = Seed.RandRange(0, Objectives[i]->PossibleLocations.Num() - 1);

		UE_LOG(LogTemp, Warning, TEXT("[Objectives] Objective #%i: Spawn #%i"), i, SelectedSpawn);

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.bNoFail;

		Objectives[i]->SpawnedActor = GetWorld()->SpawnActor<AObjectiveInteractActor>(Objectives[i]->ObjectiveActor, Objectives[i]->PossibleLocations[SelectedSpawn], SpawnInfo);

	}

}

// Called every frame
void AObjectiveHandler::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bObjectivesFinished) { return; }

	if (Objectives[CurrentObjectiveIndex]->SpawnedActor != nullptr) {
		if (Objectives[CurrentObjectiveIndex]->SpawnedActor->CheckForCompletion()) {
			Objectives[CurrentObjectiveIndex]->IsCompleted = true;

			NextObjective();
		}
	}

}

void AObjectiveHandler::NextObjective(){
	if (Objectives[CurrentObjectiveIndex + 1] == nullptr) {
		OnObjectivesFinished();
		return;
	}

	CurrentObjectiveIndex += 1;
}

void AObjectiveHandler::OnObjectivesFinished() {

	bObjectivesFinished = true;

	UE_LOG(LogTemp, Warning, TEXT("[Objectives] All objectives finished. Escape unlocked!"))

	return;
}

