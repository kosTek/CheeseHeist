// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UTextBlock;
class UImage;
class UTexture2D;
class UCanvasPanel;
class UButton;
class UHorizontalBox;

USTRUCT(BlueprintType)
struct FLevelStruct {

	GENERATED_USTRUCT_BODY();

public:
	/* Name of the level used by the engine to load */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelDefinition)
	FString LevelName;

	/* Name displayed to the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelDefinition)
	FString MapName;

};

UCLASS()
class CHEESEHEIST_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

public:

	void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	/* Main Menu Panel */

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* MainMenuPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ChooseLevelButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ChooseLevelButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* GalleryButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* GalleryButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* OptionsButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ExitButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UHorizontalBox* LevelHorizontalPanel;

	/* END Main Menu Panel */

	UPROPERTY(EditAnywhere)
	TArray<FLevelStruct> Levels;

private:

	void ChangeHoverState(UButton* Button, bool State);

	UFUNCTION(BlueprintCallable)
	void CreateLevelWidgets(TArray<FLevelStruct> LevelArray);

};
