// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "ObjectiveInteractActor.generated.h"

/**
 * 
 */
UCLASS()
class CHEESEHEIST_API AObjectiveInteractActor : public AInteractActor {
	GENERATED_BODY()
	
public:
	virtual void OnInteract(AActor* ObjectToUnlock = nullptr) override;

};
