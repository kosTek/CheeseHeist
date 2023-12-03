// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECollectableType : uint8 {

	/** Default State - Object will be deleted */
	NONE			UMETA(DisplayName = "NONE"),
	/** Highest value map objective */
	CHEESEWHEEL		UMETA(DisplayName = "Cheese Wheel"),
	/** Lowest value map objective */
	CHEESESLICE		UMETA(DisplayName = "Cheese Slice"),
	/** Map collectable, usually hidden for the player to find and not defined in objectives */
	COLLECTABLE		UMETA(DisplayName = "Collectable")

};