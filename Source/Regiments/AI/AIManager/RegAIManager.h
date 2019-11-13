// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include <atomic>

class RegAIManager
{
public:
	~RegAIManager();

	// Runs on ai thread
	void StartThread();

	// Runs on main thread
	void RequestEnd();

private:
	std::atomic<bool> bShouldEnd = false;

	void Tick();
	void EndThread();
};