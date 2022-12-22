#include "FpsCounter.h"

void FpsCounter::Init()
{
	m_numFrames = 0;
	m_framesPerSecond = 0.0;
	m_lastTime = glfwGetTime();
}

void FpsCounter::Update()
{
	double currentTime = glfwGetTime();
	m_numFrames++;
	double elapsedTime = currentTime - m_lastTime;
	if (elapsedTime >= 1.0)
	{
		m_framesPerSecond = m_numFrames / elapsedTime;
		m_numFrames = 0;
		m_lastTime = glfwGetTime();
	}
}

double FpsCounter::GetFPS() const
{
	return m_framesPerSecond;
}