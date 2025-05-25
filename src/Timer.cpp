#include "../include/Timer.h"

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
}

double Timer::getElapsedTime() const {
    std::chrono::duration<double, std::milli> elapsed = endTime - startTime;
    return elapsed.count();
}
