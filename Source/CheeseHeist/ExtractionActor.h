// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectiveInteractActor.h"
#include "ExtractionActor.generated.h"

class AObjectiveHandler;

UCLASS()
class CHEESEHEIST_API AExtractionActor : public AObjectiveInteractActor
{
	GENERATED_BODY()

	virtual void OnInteract(AActor* ObjectToUnlock = nullptr) override;

};
