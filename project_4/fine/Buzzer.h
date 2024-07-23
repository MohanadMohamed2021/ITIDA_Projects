#ifndef BUZZER_H
#define BUZZER_H

#include <wiringPi.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include "BuzzerAbstract.h"

class Buzzer : public BuzzerAbstract
{
private:
    int BuzzerPin;
    int MotorPin;
    int distance;
    char light;

public:
    Buzzer(int BuzzerPin, int MotorPin);
    void Update(int distance, char light) override;
    void Operations() override;
    ~Buzzer();
};

#endif // BUZZER_H
