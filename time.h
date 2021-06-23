#pragma once

#include "utils.h"
#include "types.h"

// Returns the value of the timer in microseconds
u64 get_time();

// Sleep ms number of miliseconds
void sleep_ms(u32 ms);

#ifdef _WIN32

#include <windows.h>

#elif __linux__

#include <time.h>

#endif