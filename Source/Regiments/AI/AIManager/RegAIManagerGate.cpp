#include "RegAIManagerGate.h"

ARegAIManagerGate::~ARegAIManagerGate()
{
	CleanThread();
}


void ARegAIManagerGate::BeginPlay()
{
	UE_LOG(LogSystems, Display, TEXT("AI Manager Gate started, starting AI Manager"));

	AIManager = new RegAIManager();
	ThreadHandle = std::thread(&RegAIManager::StartThread, AIManager);
}


void ARegAIManagerGate::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanThread();
}


void ARegAIManagerGate::CleanThread()
{
	if ((AIManager != nullptr) ^ ThreadHandle.joinable())
	{
		UE_LOG(LogSystems, Fatal, TEXT("Broken AI thread / manager state"));
	}

	if (AIManager && ThreadHandle.joinable())
	{
		UE_LOG(LogSystems, Display, TEXT("Killing AI Manager"));
		AIManager->RequestEnd();	// We trust it to delete itself (can use it in future with detach instead of join...)
		ThreadHandle.join();
		AIManager = nullptr;
		UE_LOG(LogSystems, Display, TEXT("AI Manager is no more..."));
	}
}