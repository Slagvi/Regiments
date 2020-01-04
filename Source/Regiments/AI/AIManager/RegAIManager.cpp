#include "RegAIManager.h"

#include "CoreMinimal.h" // just for logging
#include <random>


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


unsigned int RegAIManager::GetJobId()
{
	static std::uniform_int_distribution<> dis(std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max());
	static std::mt19937 gen(0);

	return dis(gen);
}


int RegAIManager::AddJob(std::shared_ptr<RegAIJob> JobInput)		// always call with std::move
{
	std::lock_guard<std::mutex> lk(JobsMutex);
	RegAIJobWrp Job;

	Job.JobData = JobInput;
	unsigned int JobId = GetJobId();
	WaitingJobs[JobId] = std::move(Job);

	return JobId;
}


void RegAIManager::UpdateJobs()
{
	std::lock_guard<std::mutex> lk(JobsMutex);
	
	while (InProgressJobs.size() < MAX_JOBS && WaitingJobs.size())
	{
		RegAIJobWrp &Job = InProgressJobs[WaitingJobs.begin()->first] = std::move(WaitingJobs.begin()->second);
		WaitingJobs.erase(WaitingJobs.begin()->first);

		Job.ExecutionFuture = std::async(std::launch::async, [this](std::shared_ptr<RegAIJob> JobData ) -> std::shared_ptr<RegAIJobResult> { return JobData->ExecuteJob(this); }, Job.JobData);
	}

	std::map<unsigned int, RegAIJobWrp>::iterator itr = InProgressJobs.begin();

	while (itr != InProgressJobs.end())
	{
		if (itr->second.ExecutionFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
		{
			JobResults[itr->first] = itr->second.ExecutionFuture.get();

			itr = InProgressJobs.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}


std::map<unsigned int, std::shared_ptr<RegAIJobResult> > RegAIManager::RetrieveResults()
{
	std::lock_guard<std::mutex> lk(JobsMutex);

	std::map<unsigned int, std::shared_ptr<RegAIJobResult> > NewResults; 
	std::swap(NewResults, JobResults);

	return NewResults;
}