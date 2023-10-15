// Fill out your copyright notice in the Description page of Project Settings.


#include "RatThrowObject.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RatCharacter.h"

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

	LastLocation = GetActorLocation();

	GetWorldTimerManager().SetTimer(RatTimerHandle, this, &ARatThrowObject::CheckRat, 1.0f, true, 2.0f);
}

// Called every frame
void ARatThrowObject::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ARatThrowObject::CheckRat() {

	FVector Location = GetActorLocation();

	if (ActorGetDistanceToCollision(LastLocation, ECC_WorldDynamic, Location) < 10) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.bNoFail;

		this->Destroy();

		GetWorld()->SpawnActor<ARatCharacter>(Rat, this->GetActorLocation() + FVector(0,0,5), FRotator(0, 0, 0), SpawnInfo);

	} else {
		LastLocation = GetActorLocation();
	}
}

