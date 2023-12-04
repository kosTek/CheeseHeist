// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectActor.h"
#include "CheeseHeistCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectActor::ACollectActor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollectType = ECollectableType::NONE;
	Player = nullptr;

}

// Called when the game starts or when spawned
void ACollectActor::BeginPlay() {
	Super::BeginPlay();
	
	if (CollectType == ECollectableType::NONE) {
		UE_LOG(LogTemp, Warning, TEXT("[CollectActor] Destroying %s due to ECollectType::NONE"), *this->GetName());

		this->Destroy();
		return;
	}

	auto* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACheeseHeistCharacter::StaticClass());
	Player = Cast<ACheeseHeistCharacter>(Actor);

	if (!Player) {
		UE_LOG(LogTemp, Warning, TEXT("[CollectActor] Destroying %s due to NO PLAYER POINTER"), *this->GetName());

		this->Destroy();
		return;
	}

}

// Called every frame
void ACollectActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ACollectActor::Interact() {
	
	Player->CollectObject(CollectType, this);

}