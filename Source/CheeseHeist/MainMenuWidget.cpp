// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScrollBox.h"
#include "Components/PanelSlot.h"

#include "Styling/SlateColor.h"

#include "LevelWidget.h"
#include "LevelList.h"


void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	//GetWidgetFromName(FName("HorizontalBox_62"))

	ChooseLevelButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnChooseLevelClicked);
	GalleryButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnGalleryClicked);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsClicked);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClicked);
	BackButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnBackClicked);

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

	if (BackButton->IsHovered()) {
		ChangeHoverState(BackButton, true);
	} else {
		ChangeHoverState(BackButton, false);
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
		ShowcaseWidget->LevelName = LevelArray[i].LevelName;
		ShowcaseWidget->SetPadding(FMargin(40.f, 0.f, 0.f, 0.f));
		
		//UScrollBox* ScrollBox = Cast<UScrollBox>(GetWidgetFromName(FName("HorizontalScrollBox")));

		UPanelSlot* PanelSlot = LevelHorizontalPanel->AddChild(ShowcaseWidget);

		if (UHorizontalBoxSlot* HorSlot = Cast<UHorizontalBoxSlot>(PanelSlot)) {
			HorSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			HorSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		}

	}

}

void UMainMenuWidget::OnBackClicked() {

	MainMenuPanel->SetVisibility(ESlateVisibility::Visible);
	BackButton->SetVisibility(ESlateVisibility::Hidden);

	// Hide all panels
	ChooseLevelPanel->SetVisibility(ESlateVisibility::Hidden);

}

void UMainMenuWidget::OnChooseLevelClicked() {

	MainMenuPanel->SetVisibility(ESlateVisibility::Hidden);
	ChooseLevelPanel->SetVisibility(ESlateVisibility::Visible);
	BackButton->SetVisibility(ESlateVisibility::Visible);

}

void UMainMenuWidget::OnGalleryClicked() {

	// Lead to gallery screen for player collectables

}

void UMainMenuWidget::OnOptionsClicked() {

	// Lead to options tab

}

void UMainMenuWidget::OnExitClicked() {

	FGenericPlatformMisc::RequestExit(false);

}
