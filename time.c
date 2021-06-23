#include "time.h"

#ifdef _WIN32

u64 get_time(){
    LARGE_INTEGER frequency, time;
    QueryPerformanceFrequency(&frequency); // @Note This value never changes so it should be cached
    QueryPerformanceCounter(&time);
    time.QuadPart *= 1000000;
    time.QuadPart /= frequency.QuadPart;
    return (u64)time.QuadPart;
}

void sleep_ms(u32 ms){
    Sleep(ms);
}

#elif __linux__

u64 get_time(){
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (u64)((1000000000*(time.tv_sec)+time.tv_nsec)/1000);
}

void sleep_ms(u32 ms){
    struct timespec time;
    time.tv_sec = ms/1000;
    time.tv_nsec = (ms*1000000)%1000000000;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &time, NULL);
}

#endif