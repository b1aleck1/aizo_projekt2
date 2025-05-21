#include "../include/Timer.h"

Timer::Timer() : running(false) {
    QueryPerformanceFrequency(&frequency);
}

void Timer::startTimer() {
    running = true;
    QueryPerformanceCounter(&start);
}

void Timer::stopTimer() {
    QueryPerformanceCounter(&end);
    running = false;
}

double Timer::getElapsedMilliseconds() const {
    if (running) {
        LARGE_INTEGER current;
        QueryPerformanceCounter(&current);
        return (current.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
    }

    return (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
}
