#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <csignal>

void signal_handle(int sig)
{
    std::cout<<"Signal "<<sig<<" has arraived...."<<std::endl;
    digitalWrite(25,LOW);
    exit(0);
}
std::mutex mux;
std::condition_variable cond;
bool flag = false;

class LedControlAbstract
{
    public:
        virtual void Update(int PinValue) = 0;
        virtual void Operations() = 0;
};
class LedControl : public LedControlAbstract
{
    private:
        int PinValue;
        int LedPin;
    public:
        LedControl(int LedPin)
        {
            this->LedPin = LedPin;
            pinMode(LedPin,OUTPUT);
        }
        void Operations()override
        {
            if (PinValue == HIGH) 
                digitalWrite(LedPin, LOW);
            else if (PinValue == LOW)
                digitalWrite(LedPin, HIGH);
        }
        void Update(int PinValue)override
        {
            this->PinValue = PinValue;
        }
};
class ButtonAbstract
{
    public:
        virtual void Subscribe(std::shared_ptr<LedControlAbstract> led) = 0;
        virtual void notify() = 0;
        virtual void setPinValue(int PinValue) = 0;
        virtual void getPinValue() = 0;
};
class Button : public ButtonAbstract
{
    private:
        int ButtonPin;
        int PinValue;
        std::vector<std::shared_ptr<LedControlAbstract>> leds;
    public:
        Button(int ButtonPin)
        {
            this->ButtonPin = ButtonPin;
            pinMode(ButtonPin,INPUT);
            pullUpDnControl(ButtonPin,PUD_UP);
        }
        void Subscribe(std::shared_ptr<LedControlAbstract> led)override
        {
            leds.push_back(led);
        }
        void notify()override
        {
            for(auto& led : leds)
            {
                led->Update(PinValue);
            }
        }
        void setPinValue(int PinValue)override
        {
            this->PinValue = PinValue;
            notify();
        }
        void getPinValue()override
        {
            int value = digitalRead(ButtonPin);
            setPinValue(value);
        }
};
void Observable(std::shared_ptr<ButtonAbstract> button)
{
    while(true)
    {
        std::unique_lock<std::mutex> guard(mux);
        button->getPinValue();
        flag = true;
        cond.notify_all();
        guard.unlock();
    }
}
void Observer(std::shared_ptr<LedControlAbstract> led)
{
    while(true)
    {
        std::unique_lock<std::mutex> guard(mux);
        cond.wait(guard,[]{return flag;});
        flag = false;
        led->Operations();
        guard.unlock();
    }
} 
int main()
{
    wiringPiSetup();
    signal(SIGINT,signal_handle);

    std::shared_ptr<LedControlAbstract> led = std::make_shared<LedControl>(25);
    std::shared_ptr<ButtonAbstract> button = std::make_shared<Button>(24);

    button->Subscribe(led);
    std::thread T1(Observable,button);
    std::thread T2(Observer,led);

    T1.join();
    T2.join();
    return 0;
}