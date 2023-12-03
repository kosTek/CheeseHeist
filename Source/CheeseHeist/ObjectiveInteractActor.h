// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "ObjectiveInteractActor.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;

class AObjectiveHandler;

UCLASS()
class CHEESEHEIST_API AObjectiveInteractActor : public AInteractActor {
	GENERATED_BODY()
	
public:
	AObjectiveInteractActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
	UBoxComponent* BoxComponent;

	AObjectiveHandler* ObjectiveHandler;

	void SetObjectiveHandler(AObjectiveHandler* Handler) { ObjectiveHandler = Handler; }

	virtual void Interact() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactable)
	bool bIsLocked;

	UFUNCTION(BlueprintCallable, Category = Interactable)
	bool GetLockStatus();

	UFUNCTION(BlueprintCallable, Category = Interactable)
	virtual void Unlock();

	UFUNCTION(BlueprintCallable, Category = Interactable)
	virtual void Lock();

	bool bIsCompleted = false;

	void SetComplete(bool Status = false);

	bool CheckForCompletion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* AnimOpenObject;

	bool IsObjectOpen = false;

	void OpenObject();

};
