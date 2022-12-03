#include "Logger.h"

TimeStep Profiler::s_timeStep;
std::string Profiler::s_label;

void consoleLog(const std::string& msg)
{
	std::cout << msg << std::endl;
}

void consoleLogError(uint32_t error)
{
	std::cerr << error << std::endl;
}

void Profiler::StartProfiling(const std::string& label)
{
	s_label = label;
	s_timeStep.start();
}

void Profiler::EndProfiling(TimeFrame timeFrame)
{
	s_timeStep.stop();
	double time = 0.0f;
	std::string timeFrameLabel;
	switch (timeFrame)
	{
	case TimeFrame::SECONDS: 
		time = s_timeStep.elapsedTimeAsSeconds();
		timeFrameLabel = "Seconds";
		break;
	case TimeFrame::MILLISECONDS:
		time = s_timeStep.elapsedTimeAsMilliseconds();
		timeFrameLabel = "Milliseconds";
		break;
	default:
		MC_CONSOLE_LOG("Invalid Profiler Time Frame");
	}
	std::cout << "[ " << s_label << ": " << time << " " << timeFrameLabel << " ]" << std::endl;
}

void profileStart(const std::string& label)
{
	Profiler::StartProfiling(label);
}

void profileEnd(Profiler::TimeFrame timeFrame)
{
	Profiler::EndProfiling(timeFrame);
}