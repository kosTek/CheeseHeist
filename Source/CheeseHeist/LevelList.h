// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelList.generated.h"

USTRUCT(BlueprintType)
struct FLevelStruct {

	GENERATED_USTRUCT_BODY();

public:
	/* Name of the level used by the engine to load */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelDefinition)
	FName LevelName;

	/* Name displayed to the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelDefinition)
	FString MapName;

};

UCLASS(Blueprintable)
class CHEESEHEIST_API ULevelList : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere)
	TArray<FLevelStruct> List;

};
