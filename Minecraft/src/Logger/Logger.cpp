#include "Logger.h"

void consoleLog(const std::string& msg)
{
	std::cout << msg << std::endl;
}

void consoleLogError(uint32_t error)
{
	std::cerr << error << std::endl;
}