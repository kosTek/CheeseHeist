// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionActor.h"
#include "ObjectiveHandler.h"

void AExtractionActor::Interact() {

	if (ObjectiveHandler == nullptr) { 
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: NO OBJECTIVE HANDLER POINTER"));
		return;
	
	}

	if (ObjectiveHandler->GetObjectivesFinished()) {
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Extraction"));

		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Objectives not finished"));

}