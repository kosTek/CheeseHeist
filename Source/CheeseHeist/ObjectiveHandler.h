// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/RandomStream.h"
#include "ObjectiveHandler.generated.h"

class AObjectiveInteractActor;
class AExtrationActor;
class UObjective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectiveFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllObjectivesFinished);

UCLASS()
class CHEESEHEIST_API AObjectiveHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveHandler();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* DELEGATES */
	FOnObjectiveFinished OnObjectiveFinished;

	UPROPERTY()
	FOnAllObjectivesFinished OnAllObjectivesFinished;

	/** Objective list in order of required completion */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
	TArray<UObjective*> Objectives;

	/** Objective that the player has to interact with or enter its bounding box to finish the level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
	UObjective* ExtractionObjective;

	/** Proceeds down the list of objectives for the player to complete */
	UFUNCTION(BlueprintCallable, Category = Objectives)
	void NextObjective();

	/** Proceeds to give a final objective to the player to finish the level */
	UFUNCTION(BlueprintCallable, Category = Objectives)
	void ObjectivesFinished();

	/** Returns the index of the current objective */
	UFUNCTION(BlueprintCallable, Category = Objectives)
	int GetCurrentObjectiveIndex();

	/** Returns the structure of the current objective */
	UFUNCTION(BlueprintCallable, Category = Objectives)
	UObjective* GetCurrentObjective();

	/** Returns the description of the objective */
	UFUNCTION(BlueprintCallable, Category = Objectives)
	FString GetCurrentObjectiveText();

	/** Returns the status of the objectives */
	UFUNCTION(BlueprintCallable, Category = Objectives)
	bool GetObjectivesFinished() { return bObjectivesFinished; }

	UFUNCTION(BlueprintCallable, Category = Seed)
	void GenerateSeed() { Seed.GenerateNewSeed(); }

	UFUNCTION(BlueprintCallable, Category = Seed)
	int32 GetSeed() { return Seed.GetCurrentSeed(); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/** Index of an objective used to read from objectives table */
	UPROPERTY(VisibleAnywhere, Category = Objectives)
	int CurrentObjectiveIndex = 0;

	/** Seed for objective spawns and minigames */
	FRandomStream Seed;

	bool bObjectivesFinished = false;

};
