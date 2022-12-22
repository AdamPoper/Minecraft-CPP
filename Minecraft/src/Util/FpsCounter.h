#pragma once

#include <GLFW/glfw3.h>

class FpsCounter
{
public:

	FpsCounter() = default;

	void Init();

	void Update();

	double GetFPS() const;

private:

	double m_lastTime;

	double m_framesPerSecond;

	uint32_t m_numFrames;
};