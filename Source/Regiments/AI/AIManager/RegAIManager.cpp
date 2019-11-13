#include "RegAIManager.h"

#include "CoreMinimal.h" // just for logging

RegAIManager::~RegAIManager()
{
	UE_LOG(LogTemp, Display, TEXT("AI Manager destroyed "));
}


void RegAIManager::StartThread()
{
	UE_LOG(LogTemp, Display, TEXT("AI thread started"));

	while (!bShouldEnd)
	{
		Tick();
	}

	EndThread();
}


void RegAIManager::RequestEnd()
{
	UE_LOG(LogTemp, Display, TEXT("AI thread end requested"));

	bShouldEnd = true;
}


void RegAIManager::Tick()
{
	if (bShouldEnd)
	{
		UE_LOG(LogTemp, Display, TEXT("why alive? :( "));
	}
}


void RegAIManager::EndThread()
{
	UE_LOG(LogTemp, Display, TEXT("AI Ended"));
	delete this;
}