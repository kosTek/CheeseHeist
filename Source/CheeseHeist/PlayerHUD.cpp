// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"

#include "CheeseHeistCharacter.h"
#include "RatCharacter.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

UPlayerHUD::UPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	ACheeseHeistCharacter* Player = Cast<ACheeseHeistCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ACheeseHeistCharacter::StaticClass()));

	if (Player) {
		Controller = Player->GetController();

		Player->OnSwitchCharacter.AddDynamic(this, &UPlayerHUD::OnCharacterSwitch);
		Player->OnThrowRat.AddDynamic(this, &UPlayerHUD::OnThrowRat);
		Player->OnPickupRat.AddDynamic(this, &UPlayerHUD::OnPickupRat);
	}

}

void UPlayerHUD::SetObjectiveText(FString Text) {

	if (Text.IsEmpty()) { Text = "Objective does not contain text!"; }

	ObjectiveText->SetText(FText::FromString(Text));

}

void UPlayerHUD::OnCharacterSwitch() {

	if (Cast<ACheeseHeistCharacter>(Controller->GetPawn()) != nullptr) {
		SwitchAbilityImage->SetBrushFromTexture(SwitchToRatTexture);

	} else if (Cast<ARatCharacter>(Controller->GetPawn()) != nullptr) {
		SwitchAbilityImage->SetBrushFromTexture(SwitchToHumanTexture);

	}

}

void UPlayerHUD::OnThrowRat() {
	SwitchAbilityImage->SetBrushFromTexture(SwitchToRatTexture);
}

void UPlayerHUD::OnPickupRat() {
	SwitchAbilityImage->SetBrushFromTexture(ThrowRatTexture);
}