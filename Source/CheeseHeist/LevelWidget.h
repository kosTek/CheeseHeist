// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class CHEESEHEIST_API ULevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
	ULevelWidget(const FObjectInitializer& ObjectInitializer);

public:

	void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* LevelButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* BorderImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* LevelPreviewImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WidgetIndex;

};
