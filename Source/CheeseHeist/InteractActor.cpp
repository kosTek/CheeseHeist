// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "CheeseHeistCharacter.h"
#include "RatCharacter.h"

// Sets default values
AInteractActor::AInteractActor() {
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	RootComponent = SkeletalMesh;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Box"));
	BoxComponent->InitBoxExtent(FVector(10,10,10));
	BoxComponent->SetCollisionProfileName("BlockAll");
	BoxComponent->SetupAttachment(RootComponent);

	bRatOnlyInteract = false;

	bIsLocked = true;

}

void AInteractActor::BeginPlay() {
	Super::BeginPlay();
	
}

void AInteractActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

bool AInteractActor::GetLockStatus() {

	return bIsLocked;

}

void AInteractActor::OnInteract(AActor* ObjectToUnlock) { // Function must be overwritten

	return;

}

bool AInteractActor::GetCanInteract() {
	return bRatOnlyInteract;
}

void AInteractActor::Unlock() {
	bIsLocked = false;
}

void AInteractActor::Lock() {
	bIsLocked = true;
}