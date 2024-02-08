// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "Components/StaticMeshComponent.h"

#include "CheeseHeistCharacter.h"
#include "RatCharacter.h"

// Sets default values
AInteractActor::AInteractActor() {
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	bRatOnlyInteract = false;

	InteractText = FText::FromString("Object Text Here");

}

void AInteractActor::BeginPlay() {
	Super::BeginPlay();
	
}

void AInteractActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AInteractActor::Interact() { // Function must be overwritten

	UE_LOG(LogTemp, Warning, TEXT("[Interact] Object has not got Interact function!"));

	return;

}

bool AInteractActor::GetCanInteract() {
	return bRatOnlyInteract;
}