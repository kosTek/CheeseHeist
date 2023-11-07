// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveHandler.h"

// Sets default values
AObjectiveHandler::AObjectiveHandler() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AObjectiveHandler::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AObjectiveHandler::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AObjectiveHandler::NextObjective(){
	return;
}

void AObjectiveHandler::OnObjectiveComplete() {
	return;
}

