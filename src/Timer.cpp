#include "../include/Timer.h"

void Timer::start() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTime);
}

void Timer::stop() {
    QueryPerformanceCounter(&endTime);
}

double Timer::getElapsedTime() const {
    return static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
}
