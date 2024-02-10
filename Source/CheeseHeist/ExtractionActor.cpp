// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionActor.h"
#include "ObjectiveHandler.h"
#include "Components/BoxComponent.h"

#include "BagObject.h"
#include "HeistGamemode.h"
#include "Kismet/GameplayStatics.h"

#include "Enumerations.h"

AExtractionActor::AExtractionActor() {

	BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExtractionActor::OnOverlapBegin);

}

void AExtractionActor::Interact() {

	if (ObjectiveHandler == nullptr) { 
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: NO OBJECTIVE HANDLER POINTER"));
		return;
	
	}

	if (ObjectiveHandler->GetObjectivesFinished()) {
		UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Extraction"));

		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Objective]: Interacted | Objectives not finished"));

}

void AExtractionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor && (OtherActor != this) && OtherComp) {

		ABagObject* Bag = Cast<ABagObject>(OtherActor);

		if (Bag != nullptr) {

			UE_LOG(LogTemp, Warning, TEXT("Bag Overlap"));

			AHeistGamemode* Gamemode = Cast<AHeistGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

			FVector2D Content = Bag->GetContent();

			if (Content.X > 0) {

				int Amount = static_cast<int>(Content.X);

				Gamemode->ChangeCheeseStored(ECollectableType::CHEESEWHEEL, Amount);
			}

			if (Content.Y > 0) {

				int Amount = static_cast<int>(Content.Y);

				Gamemode->ChangeCheeseStored(ECollectableType::CHEESEWHEEL, Amount);
			}

			Bag->Destroy();

		}

	}

}
