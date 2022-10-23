#pragma once

#include <iostream>
#include <string>

#ifdef _DEBUG
#define MC_CONSOLE_LOG(x) consoleLog(x)
#define MC_CONSOLE_LOG_ERROR(x) consoleLogError(x)
#elif defined(NDEBUG)
#define MC_CONSOLE_LOG(x)
#define MC_CONSOLE_LOG_ERROR(x)
#endif

void consoleLog(const std::string& msg);

void consoleLogError(uint32_t error);