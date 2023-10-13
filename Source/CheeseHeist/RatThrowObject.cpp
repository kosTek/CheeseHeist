// Fill out your copyright notice in the Description page of Project Settings.


#include "RatThrowObject.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ARatThrowObject::ARatThrowObject() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(Mesh);

	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ARatThrowObject::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ARatThrowObject::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

