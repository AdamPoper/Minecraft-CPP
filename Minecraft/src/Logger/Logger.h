#pragma once

#include <iostream>
#include <string>
#include "../Util/TimeStep.h"

#ifdef _DEBUG
#define MC_CONSOLE_LOG(x) consoleLog(x)
#define MC_CONSOLE_LOG_ERROR(x) consoleLogError(x)
#define MC_PROFILE_START(x) profileStart(x)
#define MC_PROFILE_END(x) profileEnd(x)
#elif defined(NDEBUG)
#define MC_CONSOLE_LOG(x) consoleLog(x)
#define MC_CONSOLE_LOG_ERROR(x) consoleLogError(x)
#define MC_PROFILE_START(x) profileStart(x)
#define MC_PROFILE_END(x) profileEnd(x)
#endif

class Profiler
{
public:

	static enum class TimeFrame
	{
		SECONDS,
		MILLISECONDS
	};

	static void StartProfiling(const std::string& label);

	static void EndProfiling(TimeFrame timeFrame);

private:

	Profiler() = default;

	Profiler(const Profiler&) = delete;

private:

	static TimeStep s_timeStep;
	static std::string s_label;
};

void consoleLog(const std::string& msg);

void consoleLogError(uint32_t error);

void profileStart(const std::string& label);

void profileEnd(Profiler::TimeFrame timeFrame);