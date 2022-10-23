#pragma once

#include <iostream>
#include <string>

#ifdef _DEBUG
#define MC_CONSOLE_LOG(x) consoleLog(x)
#elif defined(NDEBUG)
#define MC_CONSOLE_LOG(x) consoleLog(msg);
#endif

void consoleLog(const std::string& msg);