
#pragma once

#include <future>

class RegAIManager;

struct RegAIJobResult
{
public:
	unsigned int JobId;
};


class RegAIJob
{
public:


protected:
	 virtual std::shared_ptr<RegAIJobResult> ExecuteJob(RegAIManager *InJobManager); // Can return nullptr if failed
	friend class RegAIManager;
};