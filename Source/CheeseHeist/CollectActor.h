// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "Enumerations.h"
#include "CollectActor.generated.h"

class ACheeseHeistCharacter;

UCLASS()
class CHEESEHEIST_API ACollectActor : public AInteractActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	/** Define the type of collectable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collectable)
	ECollectableType CollectType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	
	ACheeseHeistCharacter* Player;

};
