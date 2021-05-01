#include "time.h"

#ifdef _WIN32

u64 get_time(){
    LARGE_INTEGER frequency, time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    time.QuadPart *= 1000000;
    time.QuadPart /= frequency.QuadPart;
    return (u64)time.QuadPart;
}

#endif