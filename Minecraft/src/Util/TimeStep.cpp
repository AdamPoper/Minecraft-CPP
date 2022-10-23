#include "TimeStep.h"

void TimeStep::start()
{
	m_start = (float)glfwGetTime();
}

void TimeStep::stop()
{
	m_end = (float)glfwGetTime();
	m_time = m_end - m_start;
}

float TimeStep::elapsedTimeAsSeconds()
{
	return m_time;
}

float TimeStep::elapsedTimeAsMilliseconds()
{
	return m_time * 1000.0f;
}