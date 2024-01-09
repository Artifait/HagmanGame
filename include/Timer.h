#pragma once
#include <chrono>

class Timer {
public:
    Timer(); 

    void Restart();         //������ �� ����� ��������� 0.f
    void Pause();           //������ �� ������
    void Start();           //������ ������

    bool IsPause();

    double GetElapsedTime();//������� ������� ������

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
    double elapsedTime = 0.0;
    bool isRunning;
};
