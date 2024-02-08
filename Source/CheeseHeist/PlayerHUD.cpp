// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"

#include "CheeseHeistCharacter.h"
#include "RatCharacter.h"
#include "InteractActor.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"

UPlayerHUD::UPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	ACheeseHeistCharacter* Player = Cast<ACheeseHeistCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ACheeseHeistCharacter::StaticClass()));

	if (Player) {
		Controller = Player->GetController();

		Player->OnSwitchCharacter.AddDynamic(this, &UPlayerHUD::OnCharacterSwitch);
		Player->OnThrowRat.AddDynamic(this, &UPlayerHUD::OnThrowRat);
		Player->OnPickupRat.AddDynamic(this, &UPlayerHUD::OnPickupRat);
	}

	bPlayerIsHuman = true;

}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);

	if (bPlayerIsHuman) { // Make rat parent of human character to make this look nicer...
		ACheeseHeistCharacter* PlayerHuman = Cast<ACheeseHeistCharacter>(Controller->GetPawn());

		if (PlayerHuman) {

			if (PlayerHuman->GetCanPickupRat()) {

				InteractText->SetText(FText::FromString("Pick up the rat"));

				InteractTextPanel->SetVisibility(ESlateVisibility::Visible);
				return;
			} else {
				InteractTextPanel->SetVisibility(ESlateVisibility::Hidden);
			}

			AInteractActor* InteractableActor = PlayerHuman->GetTargetInteractObject();

			if (InteractableActor != nullptr) {

				InteractText->SetText(InteractableActor->InteractText);

				InteractTextPanel->SetVisibility(ESlateVisibility::Visible);
			} else {
				InteractTextPanel->SetVisibility(ESlateVisibility::Hidden);
			}
		}

	} else {
		ARatCharacter* PlayerRat = Cast<ARatCharacter>(Controller->GetPawn());

		if (PlayerRat) {

			AInteractActor* InteractableActor = PlayerRat->GetTargetInteractObject();

			if (InteractableActor != nullptr) {

				InteractText->SetText(InteractableActor->InteractText);

				InteractTextPanel->SetVisibility(ESlateVisibility::Visible);
			} else {
				InteractTextPanel->SetVisibility(ESlateVisibility::Hidden);
			}

		}

	}

}

void UPlayerHUD::SetObjectiveText(FString Text) {

	if (Text.IsEmpty()) { Text = "Objective does not contain text!"; }

	ObjectiveText->SetText(FText::FromString(Text));

}

void UPlayerHUD::OnCharacterSwitch() {

	if (Cast<ACheeseHeistCharacter>(Controller->GetPawn()) != nullptr) {
		SwitchAbilityImage->SetBrushFromTexture(SwitchToRatTexture);
		bPlayerIsHuman = true;
		Crosshair->SetVisibility(ESlateVisibility::Visible);

	} else if (Cast<ARatCharacter>(Controller->GetPawn()) != nullptr) {
		SwitchAbilityImage->SetBrushFromTexture(SwitchToHumanTexture);
		bPlayerIsHuman = false;
		Crosshair->SetVisibility(ESlateVisibility::Hidden);

	}

}

void UPlayerHUD::OnThrowRat() {
	SwitchAbilityImage->SetBrushFromTexture(SwitchToRatTexture);
}

void UPlayerHUD::OnPickupRat() {
	SwitchAbilityImage->SetBrushFromTexture(ThrowRatTexture);
}