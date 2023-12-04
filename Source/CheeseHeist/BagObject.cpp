// Fill out your copyright notice in the Description page of Project Settings.


#include "BagObject.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CheeseHeistCharacter.h"

// Sets default values
ABagObject::ABagObject() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MaxCheeseWheelsInBag = 2;
	MaxCheeseSlicesInBag = 4;

}

// Called when the game starts or when spawned
void ABagObject::BeginPlay() {
	Super::BeginPlay();

	AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACheeseHeistCharacter::StaticClass());
	Player = Cast<ACheeseHeistCharacter>(Actor);

	if (Player == nullptr) {
		this->Destroy();
	}

}

// Called every frame
void ABagObject::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ABagObject::Interact() {
	
	Player->PickupBag(this);

}

void ABagObject::SetContent(int Wheels, int Slices) {

	CheeseWheelsInBag = Wheels;
	CheeseSlicesInBag = Slices;

	if ((CheeseWheelsInBag == MaxCheeseWheelsInBag) && (CheeseSlicesInBag == MaxCheeseSlicesInBag)) {
		StaticMesh->SetStaticMesh(ClosedMesh);
	} else {
		StaticMesh->SetStaticMesh(OpenedMesh);
	}

	return;

}