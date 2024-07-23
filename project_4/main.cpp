#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <csignal>
#include <wiringSerial.h>
#include <cstdlib>

int fd;
bool WriteFlag = false;
std::mutex mux;
std::condition_variable cond;
bool ExitFlag = true;

class BuzzerAbstract
{
public:
    virtual void Update(int distance, char light) = 0;
    virtual void Operations() = 0;
};

class Buzzer : public BuzzerAbstract
{
private:
    int BuzzerPin;
    int MotorPin;
    int distance;
    char light;

public:
    Buzzer(int BuzzerPin, int MotorPin)
    {
        this->MotorPin = MotorPin;
        this->BuzzerPin = BuzzerPin;
        pinMode(BuzzerPin, OUTPUT);
        pinMode(MotorPin, OUTPUT);
        digitalWrite(BuzzerPin, LOW);
        digitalWrite(MotorPin, LOW);
    }

    void Update(int distance, char light) override
    {
        this->distance = distance;
        this->light = light;
    }

    void Operations() override
    {
        static int abstcale = 0;
        if (distance <= 5)
        {
            digitalWrite(BuzzerPin, HIGH);
            digitalWrite(MotorPin, LOW);
            abstcale = 0;
        }
        else
        {
            digitalWrite(BuzzerPin, LOW);
            digitalWrite(MotorPin, HIGH);
            abstcale = 1;
        }

        int value = (light == 'o') ? 1 : 0;
        std::string data = "data=" + std::to_string(value) + ":" + std::to_string(abstcale);
        std::string post = "curl -X POST -d'" + data + "' https://MyWebPage.pythonanywhere.com/files";

        const char *post_c = post.c_str();
        system(post_c);
        std::cout << "POST request sent: " << post << std::endl;
    }

    ~Buzzer()
    {
        digitalWrite(BuzzerPin, LOW);
        digitalWrite(MotorPin, LOW);
    }
};

class SonicAbstract
{
public:
    virtual void Subscripe(std::shared_ptr<BuzzerAbstract> buzzer) = 0;
    virtual void Notify() = 0;
    virtual void setDistance() = 0;
    virtual void setIntensity() = 0;
};

class UltaSonic : public SonicAbstract
{
private:
    std::vector<std::shared_ptr<BuzzerAbstract>> buzzers;
    int distance;
    int TrigPin;
    int EchoPin;
    char light;

public:
    UltaSonic(int TrigPin, int EchoPin)
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

    void Subscripe(std::shared_ptr<BuzzerAbstract> buzzer) override
    {
        buzzers.push_back(buzzer);
    }

    void Notify() override
    {
        for (auto &buzzer : buzzers)
        {
            buzzer->Update(distance, light);
        }
    }

    void setDistance() override
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

        while (digitalRead(EchoPin) == LOW)
            ;
        double start = micros();

        while (digitalRead(EchoPin) == HIGH)
            ;
        double total_time = micros() - start;
        this->distance = total_time / 58;

        Notify();
    }

    void setIntensity() override
    {
        while(ExitFlag)
        {
            if (serialDataAvail(fd))
            {
                light = serialGetchar(fd);
                std::cout << "Data => " << light << std::endl;
                std::cout.flush();
            }
        }
    };
};
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
