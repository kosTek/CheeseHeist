// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Objective.generated.h"

class AObjectiveInteractActor;

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class CHEESEHEIST_API UObjective : public UObject
{
	GENERATED_BODY()
	
public:

	/** Interactive actor that they player has to interact to complete objective */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	TSubclassOf<AObjectiveInteractActor> ObjectiveActor = nullptr;

	/** Pointer to spawned actor */
	UPROPERTY(VisibleAnywhere, BLueprintReadOnly, Category = Objective)
	AObjectiveInteractActor* SpawnedActor = nullptr;

	/** Possible spawn locations for the objective used by Seeding */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	TArray<FTransform> PossibleLocations;

	/** Text to display to the player this objective is active */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	FString ObjectiveDescription = "Task Description";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Objective)
	bool IsCompleted = false;

	//UFUNCTION(BlueprintCallable)
	//TSubclassOf<AObjectiveInteractActor> GetObjectiveActor() { return ObjectiveActor; }

	//UFUNCTION(BlueprintCallable)
	//TArray<FTransform> GetPossibleLocations() { return PossibleLocations; }

	//UFUNCTION(BlueprintCallable)
	//FString GetObjectiveText() { return ObjectiveDescription; }

	//UFUNCTION(BlueprintCallable)
	//bool GetIsCompleted() { return IsCompleted; }

	//UFUNCTION(BlueprintCallable)
	//void SetIsCompleted(bool Status) { IsCompleted = Status; }

};
