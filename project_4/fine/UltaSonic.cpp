#include "UltaSonic.h"

int fd;
bool WriteFlag = false;
std::mutex mux;
std::condition_variable cond;
bool ExitFlag = true;

UltaSonic::UltaSonic(int TrigPin, int EchoPin)
{
    this->TrigPin = TrigPin;
    this->EchoPin = EchoPin;
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    fd = serialOpen("/dev/serial0", 115200);
    if (fd < 0)
    {
        std::cerr << "Failed to open serial port" << std::endl;
        exit(1);
    }
    std::cout << "Serial port opened successfully" << std::endl;
}

void UltaSonic::Subscripe(std::shared_ptr<BuzzerAbstract> buzzer)
{
    buzzers.push_back(buzzer);
}

void UltaSonic::Notify()
{
    for (auto &buzzer : buzzers)
    {
        buzzer->Update(distance, light);
    }
}

void UltaSonic::setDistance()
{
    static int flag = 0;
    flag++;
    if (flag == 1)
    {
        digitalWrite(TrigPin, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    digitalWrite(TrigPin, HIGH);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    digitalWrite(TrigPin, LOW);

    while (digitalRead(EchoPin) == LOW);
    double start = micros();

    while (digitalRead(EchoPin) == HIGH);
    double total_time = micros() - start;
    this->distance = total_time / 58;

    Notify();
}

void UltaSonic::setIntensity()
{
    while (ExitFlag)
    {
        if (serialDataAvail(fd))
        {
            light = serialGetchar(fd);
            std::cout << "Data => " << light << std::endl;
            std::cout.flush();
        }
    }
}
