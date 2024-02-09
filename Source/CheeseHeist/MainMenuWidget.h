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
class ULevelWidget;
class ULevelList;

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
	UCanvasPanel* ChooseLevelPanel;

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULevelWidget> LevelPanel;

	/* END Main Menu Panel */

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULevelList> Levels;

private:

	void ChangeHoverState(UButton* Button, bool State);

	UFUNCTION(BlueprintCallable)
	void CreateLevelWidgets();

};
