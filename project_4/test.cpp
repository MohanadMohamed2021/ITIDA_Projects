#include <wiringPi.h>
#include <iostream>
#include <thread>

#define TRIG 0 // GPIO23
#define ECHO 2 // GPIO24

void setup()
{
    wiringPiSetup();
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Ensure TRIG is low initially
    digitalWrite(TRIG, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

int main(void)
{
    setup();

    while (1)
    {
        // Send a 10us pulse to trigger
        digitalWrite(TRIG, HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        digitalWrite(TRIG, LOW);

        // Wait for ECHO to go HIGH
        while (digitalRead(ECHO) == LOW)
            ;

        // Measure the duration of the ECHO pulse
        long startTime = micros();
        while (digitalRead(ECHO) == HIGH)
            ;
        long travelTime = micros() - startTime;

        // Calculate the distance
        int distance = travelTime / 58;

        printf("Distance: %d cm\n", distance);

        delay(1000); // Wait for a second before the next measurement
    }

    return 0;
}
