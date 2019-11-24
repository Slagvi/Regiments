// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Regiments.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegRegimentTemplate.generated.h"

UCLASS(Blueprintable)
class URegRegimentTemplate : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 MaxUnitsNum;

	UPROPERTY(EditDefaultsOnly)
	int32 MinUnitsNum;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxHpPoints;

	UPROPERTY(EditDefaultsOnly)
	float MaxSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SoldierClass;
};