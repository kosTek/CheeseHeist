// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HeistGamemode.generated.h"

class ACheeseHeistCharacter;
class AObjectiveHandler;

class UPlayerHUD;


UCLASS()
class CHEESEHEIST_API AHeistGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHeistGamemode();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<UPlayerHUD> HUDWidget;

	UPROPERTY(VisibleAnywhere, Category = HUD)
	UPlayerHUD* HUD;

private:

	UPROPERTY()
	ACheeseHeistCharacter* MainCharacter;

	UPROPERTY()
	AObjectiveHandler* ObjectiveHandler;

	UFUNCTION()
	void OnObjectiveFinished();

	UFUNCTION()
	void OnAllObjectivesFinished();

};
