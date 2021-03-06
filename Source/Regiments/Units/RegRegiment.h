// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "Regiments.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegRegimentState.h"
#include "RegRegimentTemplate.h"
#include "RegRegiment.generated.h"

UCLASS(Blueprintable)
class ARegRegiment : public AActor
{
	GENERATED_BODY()

	ARegRegiment();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf <URegRegimentTemplate> TemplateType;

	UPROPERTY(EditAnywhere)
	FTransform TargetTransform;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void RecreateSoldiers(FTransform StartTransform);
	virtual void UpdateSoldiersMovement(float DeltaTime);

	UPROPERTY()
	TArray<AActor *> DisplayedSoldiers;

	UPROPERTY()
	URegRegimentTemplate* Template;

	FRegRegimentState State;

private:
	FVector GetRegimentLocation();
};