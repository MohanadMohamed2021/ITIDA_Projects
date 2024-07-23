#include "Buzzer.h"

Buzzer::Buzzer(int BuzzerPin, int MotorPin)
{
    this->MotorPin = MotorPin;
    this->BuzzerPin = BuzzerPin;
    pinMode(BuzzerPin, OUTPUT);
    pinMode(MotorPin, OUTPUT);
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(MotorPin, LOW);
}

void Buzzer::Update(int distance, char light)
{
    this->distance = distance;
    this->light = light;
}

void Buzzer::Operations()
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

Buzzer::~Buzzer()
{
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(MotorPin, LOW);
}
