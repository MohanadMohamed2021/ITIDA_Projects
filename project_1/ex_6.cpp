#include <iostream>
#include <csignal>
#include <wiringPi.h>
#include <thread>

class UltraSonic
{
    private:
        int trig;
        int echo;
    public:
        UltraSonic(int trig,int echo)
        {
            this->trig = trig;
            this->echo = echo;
            pinMode(trig,OUTPUT);
            pinMode(echo,INPUT);
            digitalWrite(trig,LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        double getDistance()
        {
            digitalWrite(trig,HIGH);
            std::this_thread::sleep_for(std::chrono::microseconds(10));
            digitalWrite(trig,LOW);

            while(digitalRead(echo) == LOW);
            double start_time = micros();
            while(digitalRead(echo) == HIGH);
            double travel = micros() - start_time;
            double distance = travel / 58;
            return distance;
        }
};
int main()
{
    wiringPiSetup();
    UltraSonic sonic(8,9);
    while (true)
    {
        double distance = sonic.getDistance();
        std::cout<<"Distance => "<<distance<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}

