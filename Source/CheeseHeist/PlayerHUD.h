// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"


class UTextBlock;
class UImage;
class UTexture2D;

UCLASS()
class CHEESEHEIST_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
	UPlayerHUD(const FObjectInitializer& ObjectInitializer);

	// Objectives
public:

	UFUNCTION(BlueprintCallable)
	void SetObjectiveText(FString Text);

	/** Displays current objective text */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ObjectiveText;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* SwitchAbilityImage;

	UPROPERTY(EditAnywhere, Category = Images)
	UTexture2D* ThrowRatTexture;

	UPROPERTY(EditAnywhere, Category = Images)
	UTexture2D* SwitchToHumanTexture;

	UPROPERTY(EditAnywhere, Category = Images)
	UTexture2D* SwitchToRatTexture;

private:

	UPROPERTY()
	class AController* Controller;

	UFUNCTION()
	void OnCharacterSwitch();

	UFUNCTION()
	void OnThrowRat();

	UFUNCTION()
	void OnPickupRat();


};
