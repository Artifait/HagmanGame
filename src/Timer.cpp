#include <Timer.h>

Timer::Timer()
{
    isRunning = false;
    startTime = std::chrono::high_resolution_clock::now();
}
void Timer::Restart()
{
    isRunning = false;
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::Pause()
{
    if (isRunning) {
        endTime = std::chrono::high_resolution_clock::now();
        elapsedTime += std::chrono::duration<double>(endTime - startTime).count();
        isRunning = false;
    }
}

void Timer::Start()
{
    if (!isRunning) {
        startTime = std::chrono::high_resolution_clock::now();
        isRunning = true;
    }
}

double Timer::GetElapsedTime()
{
    if (isRunning) {
        endTime = std::chrono::high_resolution_clock::now();
        return elapsedTime + std::chrono::duration<double>(endTime - startTime).count();
    }
    else {
        return elapsedTime;
    }
}

bool Timer::IsPause()
{
    return !isRunning;
}