#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/**
 *@brief Klasa Timer służy do pomiaru czasu wykonywania operacji.
 * Wykorzystuje std::chrono::high_resolution_clock dla dokładnych pomiarów.
 */

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

public:
    // Rozpoczyna pomiar czasu.
    void start();

    // Kończy pomiar czasu.
    void stop();

    // Zwraca zmierzony czas w milisekundach.
    double getElapsedTime() const;
};

#endif
