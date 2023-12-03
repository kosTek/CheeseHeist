// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "BagObject.generated.h"

class UStaticMeshComponent;
class UStaticMesh;
class ACheeseHeistCharacter;

UCLASS()
class CHEESEHEIST_API ABagObject : public AInteractActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABagObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bag)
	UStaticMesh* ClosedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bag)
	UStaticMesh* OpenedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bag)
	int MaxCheeseWheelsInBag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bag)
	int MaxCheeseSlicesInBag;

	virtual void Interact() override;

	/** Sets the content of bags - Called on creation */
	UFUNCTION(BlueprintCallable, Category = Bag)
	void SetContent(int Wheels, int Slices);

	/** Returns the contents of the bag in a vector 2D format - X = Cheese Wheels Y = Cheese Slices */
	UFUNCTION(BlueprintCallable, Category = Bag)
	FVector2D GetContent() { return FVector2D(CheeseWheelsInBag, CheeseSlicesInBag); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	
	UPROPERTY()
	int CheeseWheelsInBag;

	UPROPERTY()
	int CheeseSlicesInBag;

	UPROPERTY()
	ACheeseHeistCharacter* Player;

};
