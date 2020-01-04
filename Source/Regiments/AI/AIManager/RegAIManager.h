
#pragma once

#include <atomic>
#include <mutex>
#include <set>
#include <map>
#include "AI/AIJob/RegAIJob.h"

struct RegAIJobWrp
{
public:
	std::shared_ptr<RegAIJob> JobData;
	std::future<std::shared_ptr<RegAIJobResult> > ExecutionFuture;
};

class RegAIManager
{
public:
	~RegAIManager();

	// Runs on ai thread
	void StartThread();

	// Runs on main thread
	void RequestEnd();

	// Runs on main thread, called by gameplay
	int AddJob(std::shared_ptr<RegAIJob> JobInput); // return job id that can be later used by game to retrieve results

	std::map<unsigned int, std::shared_ptr<RegAIJobResult> > RetrieveResults();

private:
	static const int MAX_JOBS = 4;

	std::atomic<bool> bShouldEnd = false;
	std::mutex JobsMutex;

	std::map<unsigned int, RegAIJobWrp> WaitingJobs; // before ExecuteJob
	std::map<unsigned int, RegAIJobWrp> InProgressJobs; // during ExecuteJob
	std::map<unsigned int, std::shared_ptr<RegAIJobResult> > JobResults; // during ExecuteJob

	void Tick();
	void EndThread();
	void UpdateJobs();
	unsigned int GetJobId();
};