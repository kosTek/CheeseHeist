// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelSlot.h"

#include "Styling/SlateColor.h"

#include "LevelWidget.h"
#include "LevelList.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	//GetWidgetFromName(FName("HorizontalBox_62"))

	return;

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

void UMainMenuWidget::CreateLevelWidgets() {

	if (Levels == nullptr) { return; }
	if (LevelPanel == nullptr) { return; }

	TArray<FLevelStruct> LevelArray = Levels.GetDefaultObject()->List;

	for (int i = 0; i < LevelArray.Num(); i++) {

		ULevelWidget* ShowcaseWidget = CreateWidget<ULevelWidget>(this, LevelPanel);
		ShowcaseWidget->LevelText->SetText(FText::FromString(LevelArray[i].MapName));
		ShowcaseWidget->WidgetIndex = i;
		ShowcaseWidget->SetPadding(FMargin(40.f, 0.f, 0.f, 0.f));
		
		UPanelSlot* PanelSlot = LevelHorizontalPanel->AddChild(ShowcaseWidget);

		if (UHorizontalBoxSlot* HorSlot = Cast<UHorizontalBoxSlot>(PanelSlot)) {
			HorSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			HorSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		}

	}

}