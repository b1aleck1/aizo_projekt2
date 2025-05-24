#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

class Timer {
private:
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    LARGE_INTEGER frequency;
    bool running;

public:
    Timer();
    void startTimer();
    void stopTimer();
    double getElapsedMilliseconds() const;
};

#endif // TIMER_H
