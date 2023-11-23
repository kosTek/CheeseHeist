// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "ObjectiveInteractActor.generated.h"

class AObjectiveHandler;

UCLASS()
class CHEESEHEIST_API AObjectiveInteractActor : public AInteractActor {
	GENERATED_BODY()
	
public:
	AObjectiveHandler* ObjectiveHandler;

	void SetObjectiveHandler(AObjectiveHandler* Handler) { ObjectiveHandler = Handler; }

	virtual void OnInteract(AActor* ObjectToUnlock = nullptr) override;

	bool bIsCompleted = false;

	void SetComplete(bool Status = false);

	bool CheckForCompletion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* AnimOpenObject;

	bool IsObjectOpen = false;

	void OpenObject();

};
