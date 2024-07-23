#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <csignal>
#include "SonicAbstract.h"
#include "BuzzerAbstract.h"

extern int fd;
extern bool WriteFlag;
extern std::mutex mux;
extern std::condition_variable cond;
extern bool ExitFlag;

class UltaSonic : public SonicAbstract
{
private:
    std::vector<std::shared_ptr<BuzzerAbstract>> buzzers;
    int distance;
    int TrigPin;
    int EchoPin;
    char light;

public:
    UltaSonic(int TrigPin, int EchoPin);
    void Subscripe(std::shared_ptr<BuzzerAbstract> buzzer) override;
    void Notify() override;
    void setDistance() override;
    void setIntensity() override;
};

#endif // ULTRASONIC_H
