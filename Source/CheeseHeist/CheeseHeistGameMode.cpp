// Copyright Epic Games, Inc. All Rights Reserved.

#include "CheeseHeistGameMode.h"
#include "CheeseHeistCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACheeseHeistGameMode::ACheeseHeistGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
