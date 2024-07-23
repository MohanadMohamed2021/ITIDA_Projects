#include <iostream>
#include <csignal>
#include <wiringPi.h>
#include <thread>
#include <memory>

class Command
{
public:
    virtual void execute() = 0;
};

class PWM_Control
{
private:
    int BaseClock;
    int ClockRange;
    int Freq;
    int PWMClock;
    double DutyCycle;
    int PWM_Pin;

public:
    PWM_Control(int PWM_Pin, double DutyCycle)
    {
        this->PWM_Pin = PWM_Pin;
        this->DutyCycle = DutyCycle;
        BaseClock = 19200000;
        ClockRange = 1024;
        pinMode(PWM_Pin, PWM_OUTPUT);
        pwmSetMode(PWM_MODE_MS);
        pwmSetRange(ClockRange);
    }

    void setClock(int Freq)
    {
        this->Freq = Freq;
        PWMClock = (BaseClock / (Freq * ClockRange));
        pwmSetClock(PWMClock);
    }

    void startPWM()
    {
        while (true)
        {
            double delay = (1.0 / Freq) * 1000000; // delay in microseconds
            double duty = (DutyCycle * ClockRange);
            pwmWrite(PWM_Pin, static_cast<int>(duty));
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(delay)));
        }
    }
};

class CommandSetClock : public Command
{
private:
    std::shared_ptr<PWM_Control> PWM;

public:
    CommandSetClock(std::shared_ptr<PWM_Control> cp_PWM) : PWM(cp_PWM) {}

    void execute() override
    {
        int Freq;
        std::cout << "Enter Freq => ";
        std::cin >> Freq;
        PWM->setClock(Freq);
    }
};

class CommandStartPWM : public Command
{
private:
    std::shared_ptr<PWM_Control> PWM;

public:
    CommandStartPWM(std::shared_ptr<PWM_Control> cp_PWM) : PWM(cp_PWM) {}

    void execute() override
    {
        PWM->startPWM();
    }
};

class Invoker
{
private:
    std::shared_ptr<Command> command;

public:
    void setCommand(std::shared_ptr<Command> cp_command)
    {
        command = cp_command;
    }

    void Execute()
    {
        command->execute();
    }
};

void System(Invoker &invoker, std::shared_ptr<Command> setClock)
{
    while (true)
    {
        invoker.setCommand(setClock);
        invoker.Execute();
    }
}

int main()
{
    wiringPiSetup();
    std::shared_ptr<PWM_Control> PWM = std::make_shared<PWM_Control>(26, 0.5);
    std::shared_ptr<Command> setClock = std::make_shared<CommandSetClock>(PWM);
    std::shared_ptr<Command> Run = std::make_shared<CommandStartPWM>(PWM);

    Invoker invoker;
    invoker.setCommand(setClock);
    invoker.Execute();

    std::thread T1(System, std::ref(invoker), setClock);

    invoker.setCommand(Run);
    invoker.Execute();

    T1.join();
    return 0;
}
