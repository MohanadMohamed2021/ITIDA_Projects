#include <wiringPi.h>
#include <thread>
#include <memory>
#include <csignal>
#include <wiringSerial.h>
#include "Buzzer.h"
#include "UltaSonic.h"

void SonicOperate(std::shared_ptr<SonicAbstract> sonic)
{
    while (ExitFlag)
    {
        std::unique_lock<std::mutex> guard(mux);
        sonic->setDistance();
        WriteFlag = true;
        cond.notify_all();
        guard.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void BuzzerOperate(std::shared_ptr<BuzzerAbstract> buzzer)
{
    while (ExitFlag)
    {
        std::unique_lock<std::mutex> guard(mux);
        cond.wait(guard, []
                  { return WriteFlag; });
        WriteFlag = false;
        buzzer->Operations();
        guard.unlock();
    }
}

void Intensity(std::shared_ptr<SonicAbstract> sonic)
{
    sonic->setIntensity();
}

void signal_handle(int sig)
{
    ExitFlag = false;
    system("espeak -v en-gb -s 50 -p 100 -a 1000 'Goodbye mahetab animal dog'");
    digitalWrite(27, LOW);
    digitalWrite(3, LOW);
    serialClose(fd);
    exit(0);
}

int main()
{
    signal(SIGINT, signal_handle);
    wiringPiSetup();
    std::shared_ptr<BuzzerAbstract> buzzer = std::make_shared<Buzzer>(27, 3);
    std::shared_ptr<SonicAbstract> sonic = std::make_shared<UltaSonic>(0, 2);

    sonic->Subscripe(buzzer);
    std::thread T1(SonicOperate, sonic);
    std::thread T2(BuzzerOperate, buzzer);
    std::thread T3(Intensity, sonic);

    T1.join();
    T2.join();
    T3.join();
    return 0;
}
