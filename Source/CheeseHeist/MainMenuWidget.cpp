// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

#include "Styling/SlateColor.h"

#include "LevelWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	
	UE_LOG(LogTemp, Warning, TEXT("%i"), Levels.Num());

	for (int i = 0; i < Levels.Num(); i++) {

		ULevelWidget* Widget = CreateWidget<ULevelWidget>(this, ULevelWidget::StaticClass());
		Widget->LevelText->SetText(FText::FromString(Levels[i].MapName));
		Widget->WidgetIndex = i;

		LevelHorizontalPanel->AddChild(Widget);

		Widget->SetPadding(FMargin(40.f, 0.f, 0.f, 0.f));

		UE_LOG(LogTemp, Warning, TEXT("%i Processed"), i);

	}

}

void UMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);

	if (ChooseLevelButton->IsHovered()) {
		ChangeHoverState(ChooseLevelButton, true);
	} else {
		ChangeHoverState(ChooseLevelButton, false);
	}

	if (GalleryButton->IsHovered()) {
		ChangeHoverState(GalleryButton, true);
	} else {
		ChangeHoverState(GalleryButton, false);
	}

	if (OptionsButton->IsHovered()) {
		ChangeHoverState(OptionsButton, true);
	} else {
		ChangeHoverState(OptionsButton, false);
	}

	if (ExitButton->IsHovered()) {
		ChangeHoverState(ExitButton, true);
	} else {
		ChangeHoverState(ExitButton, false);
	}

}

void UMainMenuWidget::ChangeHoverState(UButton* Button, bool State) {

	if (!Button) { return; }

	UTextBlock* Text = Cast<UTextBlock>(Button->GetChildAt(0));

	if (Text) {
		
		if (State) {
			FSlateColor Color = FSlateColor(FLinearColor(255.f / 255.f, 0.f / 255.f, 0.f / 255.f, 1.f));
			Text->SetColorAndOpacity(Color);
		} else {
			FSlateColor Color = FSlateColor(FLinearColor(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f));
			Text->SetColorAndOpacity(Color);
		}

	}

}

void UMainMenuWidget::CreateLevelWidgets(TArray<FLevelStruct> LevelArray) {
	Levels = LevelArray;

	

}