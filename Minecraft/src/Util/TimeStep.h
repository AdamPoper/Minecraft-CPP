#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TimeStep
{
public:
	void start();

	void stop();

	float elapsedTimeAsMilliseconds();

	float elapsedTimeAsSeconds();

	operator float() const { return m_time; }

private:

	float m_time, m_start, m_end;
};