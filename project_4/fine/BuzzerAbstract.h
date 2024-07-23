#ifndef BUZZER_ABSTRACT_H
#define BUZZER_ABSTRACT_H

class BuzzerAbstract
{
public:
    virtual void Update(int distance, char light) = 0;
    virtual void Operations() = 0;
};

#endif // BUZZER_ABSTRACT_H
