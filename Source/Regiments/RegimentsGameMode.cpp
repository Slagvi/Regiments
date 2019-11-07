// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RegimentsGameMode.h"
#include "RegimentsPawn.h"

ARegimentsGameMode::ARegimentsGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ARegimentsPawn::StaticClass();
}

