#ifndef TIMER_H
#define TIMER_H

#include <windows.h> // For QueryPerformanceCounter
// Alternative: #include <chrono> for std::chrono::high_resolution_clock

class Timer {
private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    bool running;

public:
    Timer();
    void startTimer();
    void stopTimer();
    double getElapsedMilliseconds() const;
    bool isRunning() const { return running; }
};

#endif // TIMER_H
