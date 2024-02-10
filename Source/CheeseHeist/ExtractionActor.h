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

	AExtractionActor();

public:

	virtual void Interact() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

