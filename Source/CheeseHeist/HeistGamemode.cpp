// Fill out your copyright notice in the Description page of Project Settings.


#include "HeistGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"

#include "CheeseHeistCharacter.h"
#include "PlayerHUD.h"
#include "ObjectiveHandler.h"

AHeistGamemode::AHeistGamemode() : Super() {

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	ObjectiveHandler = nullptr;
	HUD = nullptr;

}

void AHeistGamemode::BeginPlay() {
	Super::BeginPlay();

	MainCharacter = Cast<ACheeseHeistCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ACheeseHeistCharacter::StaticClass()));

	if (MainCharacter) {
		
	}

	ObjectiveHandler = Cast<AObjectiveHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AObjectiveHandler::StaticClass()));

	if (ObjectiveHandler) {
		ObjectiveHandler->OnObjectiveFinished.AddDynamic(this, &AHeistGamemode::OnObjectiveFinished);
		ObjectiveHandler->OnAllObjectivesFinished.AddDynamic(this, &AHeistGamemode::OnAllObjectivesFinished);

		UE_LOG(LogTemp, Warning, TEXT("[Gamemode] Objective Handler delegates bound!"));
	}

	if (HUDWidget != NULL) {
		HUD = CreateWidget<UPlayerHUD>(UGameplayStatics::GetGameInstance(GetWorld()), HUDWidget);
		HUD->AddToViewport();
		HUD->SetObjectiveText(ObjectiveHandler->GetCurrentObjectiveText());
		UE_LOG(LogTemp, Warning, TEXT("[Gamemode] HUD Created!"));
	}

}

void AHeistGamemode::OnObjectiveFinished() {

	HUD->SetObjectiveText(ObjectiveHandler->GetCurrentObjectiveText());

	UE_LOG(LogTemp, Warning, TEXT("[Gamemode] Delegate Called"));

}

void AHeistGamemode::OnAllObjectivesFinished() {

	// Check if all cheese has been collected
		// Display secondary objective if not
		// If all collected instruct to extract

	HUD->SetObjectiveText("All objectives finished!"); // Debug

	UE_LOG(LogTemp, Warning, TEXT("[Gamemode] Delegate Called"));

}