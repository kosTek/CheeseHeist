// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RatThrowObject.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class ARatCharacter;

UCLASS()
class ARatThrowObject : public AActor {
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ARatThrowObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSubclassOf<ARatCharacter> Rat;

private:

	FVector LastLocation;

	FTimerHandle RatTimerHandle;

	UFUNCTION()
	void CheckRat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
