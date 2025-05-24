#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

class Timer {
public:
    void start();
    void stop();
    double getElapsedTime() const;

private:
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    LARGE_INTEGER frequency;
};

#endif // TIMER_H
