// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"

void ULevelWidget::NativeConstruct() {

	LevelButton->OnClicked.AddDynamic(this, &ULevelWidget::LevelSelected);

}

void ULevelWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);

	if (LevelButton->IsHovered()) {
		ChangeHoverState(LevelButton, true);
	} else {
		ChangeHoverState(LevelButton, false);
	}

}

void ULevelWidget::ChangeHoverState(UButton* Button, bool State) {

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

void ULevelWidget::LevelSelected() {

	if (LevelName.ToString().IsEmpty()) { return; }

	UGameplayStatics::OpenLevel(GetGameInstance(), LevelName);

}
