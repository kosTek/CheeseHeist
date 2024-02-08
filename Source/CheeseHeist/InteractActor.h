// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractActor.generated.h"

class ACheeseHeistCharacter;
class ARatCharacter;

class UStaticMeshComponent;

UCLASS()
class CHEESEHEIST_API AInteractActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
	bool bRatOnlyInteract;

	UFUNCTION(BlueprintCallable, Category = Interactable)
	virtual void Interact();

	UFUNCTION(BlueprintCallable, Category = Interactable)
	bool GetCanInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
	FText InteractText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/*UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/
};
