#include "header.hpp"
#include <iostream>

long double CPP::hms_to_secs(int hours,int minutes,int seconds)
{
    return (long double)((double)(3600*hours)+(double)(60*minutes)+(double)(seconds));
}

CPP::TollBooth::TollBooth():total_money(0),total_cars(0){}
void CPP::TollBooth::payingCar()
{
    total_money+=0.5;
    total_cars++;
}
void CPP::TollBooth::nopayingCar()
{
    total_money+=0.5;
}
void CPP::TollBooth::Display()
{
    std::cout<<"Total cars is >> "<<total_cars<<"  Total money is >> "<<total_money<<std::endl;
}
CPP::Time::Time(int cp_hours,int cp_minutes,int cp_seconds):hours(cp_hours),minutes(cp_minutes),seconds(cp_seconds){}
void CPP::Time::Display()
{
    std::cout<<"the time is >> "<<hours<<":"<<minutes<<":"<<seconds<<std::endl;
}
void CPP::Time::Add(Time obj1,Time obj2)
{
    seconds = seconds + obj1.seconds + obj2.seconds;
    if(seconds>=60)
    {
        seconds-=60;
        minutes++;
    }
    minutes = minutes + obj1.minutes + obj2.minutes;
    if(minutes>=60)
    {
        minutes-=60;
        hours++;
    }
    hours = hours + obj1.hours + obj2.hours;
}
CPP::Time CPP::Time::operator+(Time obj)
{
    seconds = seconds + obj.seconds;
    if(seconds>=60)
    {
        seconds-=60;
        minutes++;
    }
    minutes = minutes + obj.minutes;
    if(minutes>=60)
    {
        minutes-=60;
        hours++;
    }
    hours = hours + obj.hours;
    return Time(hours,minutes,seconds);
}
void CPP::Time::operator++()
{
    seconds++;
    if(seconds>=60)
    {
        seconds-=60;
        minutes++;
    }
    if(minutes>=60)
    {
        minutes-=60;
        hours++;
    }
}
void CPP::Time::operator--()
{
    seconds--;
    if(seconds==0 && minutes>0)
    {
        seconds+=60;
        minutes--;
    }
    if(minutes==60 && hours>0)
    {
        minutes+=60;
        hours--;
    }
}
CPP::Count::Count():counter(0){}
void CPP::Count::increment()
{
    counter++;
}
void CPP::Count::decrement()
{
    counter--;
}
void CPP::Count::Display()
{
    std::cout<<"The counter >> "<<counter<<std::endl;
}
void CPP::Count::operator++()
{
    counter+=step;
}
void CPP::Count::operator--()
{
    counter-=step;
}
CPP::Count::Count(int cp_step):step(cp_step),counter(0){}
CPP::SimpleCounter& CPP::SimpleCounter::SimpleCounter_increment()
{
    CPP::Count::increment();
    return *this;
}
CPP::ExtendedCounter::ExtendedCounter(int cp_steper):CPP::Count::Count(cp_steper){}
CPP::ExtendedCounter& CPP::ExtendedCounter::ExtendedCounter_increment()
{
    CPP::Count::operator++();
    return *this;
}
CPP::ExtendedCounter& CPP::ExtendedCounter::ExtendedCounter_decrement()
{
    CPP::Count::operator--();
    return *this;
}
int CPP::Serial::serial=0;
CPP::Serial::Serial()
{
    serial++;
    serial_number=serial;
}
void CPP::Serial::Display()
{
    std::cout<<"Ther seral number of this object is >> "<<serial_number<<std::endl;
}