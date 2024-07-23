#ifndef SONIC_ABSTRACT_H
#define SONIC_ABSTRACT_H

#include <memory>
#include "BuzzerAbstract.h"

class SonicAbstract
{
public:
    virtual void Subscripe(std::shared_ptr<BuzzerAbstract> buzzer) = 0;
    virtual void Notify() = 0;
    virtual void setDistance() = 0;
    virtual void setIntensity() = 0;
};

#endif // SONIC_ABSTRACT_H
