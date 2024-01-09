#pragma once
#include <chrono>

class Timer {
public:
    Timer(); 

    void Restart();         //таймер на паузу состояние 0.f
    void Pause();           //таймер не тикает
    void Start();           //таймер тикает

    bool IsPause();

    double GetElapsedTime();//сколько времени тикает

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
    double elapsedTime = 0.0;
    bool isRunning;
};
