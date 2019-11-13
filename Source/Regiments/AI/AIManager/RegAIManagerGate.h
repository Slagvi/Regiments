// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once


#include <thread>
#include "Regiments.h"
#include "RegAIManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegAIManagerGate.generated.h"

UCLASS(Blueprintable)
class ARegAIManagerGate : public AActor
{
	GENERATED_BODY()

	~ARegAIManagerGate();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	RegAIManager* AIManager = nullptr;
	std::thread ThreadHandle;

	void CleanThread();
};