#include <iostream>
#include <thread>
#include <wiringPi.h>
#include <memory>
#include <map>

class Command
{
public:
    virtual void execute() = 0;
};

class LedControl
{
private:
    int LedPin;
    int ToggleTime;

public:
    LedControl(int LedPin, int ToggleTime)
    {
        this->LedPin = LedPin;
        this->ToggleTime = ToggleTime;
        wiringPiSetup();
        pinMode(LedPin, OUTPUT);
        digitalWrite(LedPin, LOW);
    }
    void LedOn()
    {
        digitalWrite(LedPin, HIGH);
    }
    void LedOff()
    {
        digitalWrite(LedPin, LOW);
    }
    void Toggle()
    {
        digitalWrite(LedPin, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(ToggleTime));
        digitalWrite(LedPin, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(ToggleTime));
    }
    ~LedControl()
    {
        digitalWrite(LedPin, LOW);
    }
};

class CommandTurnOn : public Command
{
private:
    std::shared_ptr<LedControl> led;

public:
    CommandTurnOn(std::shared_ptr<LedControl> cp_led) : led(cp_led) {}
    void execute() override
    {
        led->LedOn();
    }
};

class CommandTurnOff : public Command
{
private:
    std::shared_ptr<LedControl> led;

public:
    CommandTurnOff(std::shared_ptr<LedControl> cp_led) : led(cp_led) {}
    void execute() override
    {
        led->LedOff();
    }
};

class CommandToggle : public Command
{
private:
    std::shared_ptr<LedControl> led;

public:
    CommandToggle(std::shared_ptr<LedControl> cp_led) : led(cp_led) {}
    void execute() override
    {
        led->Toggle();
    }
};

class Invoke
{
private:
    std::shared_ptr<Command> command;

public:
    void setCommand(std::shared_ptr<Command> cp_command)
    {
        command = cp_command;
    }
    void executeCommand()
    {
        command->execute();
    }
};

int main()
{
    std::map<std::string, std::shared_ptr<Command>> userChoice;
    int LedPin, ToggleTime;
    std::string choice;

    std::cout << "Enter LedPin => ";
    std::cin >> LedPin;
    std::cout << "Enter ToggleTime => ";
    std::cin >> ToggleTime;

    std::shared_ptr<LedControl> ledControl = std::make_shared<LedControl>(LedPin,ToggleTime);

    std::shared_ptr<Command> OnCommand = std::make_shared<CommandTurnOn>(ledControl);
    std::shared_ptr<Command> OffCommand = std::make_shared<CommandTurnOff>(ledControl);
    std::shared_ptr<Command> ToggleCommand = std::make_shared<CommandToggle>(ledControl);

    userChoice["on"] = OnCommand;
    userChoice["off"] = OffCommand;
    userChoice["toggle"] = ToggleCommand;

    std::cout << "--------- Welcome to Led Control system ----------" << std::endl;

    while (true)
    {
        std::cout << "-------------------------------------\n"
                     "Enter 'on' to turn on led\n"
                     "Enter 'off' to turn off led\n"
                     "Enter 'toggle' to toggle led\n"
                     "==> ";
        std::cin >> choice;
        if (userChoice[choice] != NULL)
        {
            std::shared_ptr<Invoke> invoker = std::make_shared<Invoke>();
            invoker->setCommand(userChoice[choice]);
            invoker->executeCommand();
        }
        else
        {
            break;
        }
    }
    return 0;
}