#pragma once

namespace CPP
{
    long double hms_to_secs(int hours,int minutes,int seconds);
    class TollBooth
    {
        private:
            float total_money;
            int total_cars;
        public:
            TollBooth();
            void payingCar();
            void nopayingCar();
            void Display();
    };
    class Time
    {
        private:
            int hours;
            int minutes;
            int seconds;
        public:
            Time(int cp_hours,int cp_minutes,int cp_seconds);
            void Display();
            void Add(Time obj1,Time obj2);
            Time operator+(Time obj);
            void operator++();
            void operator--();
    };
    class Count
    {
        private:
            int counter;
            int step;
        public:
            Count();
            Count(int cp_step);
            void increment();
            void decrement();
            void operator++();
            void operator--();
            void Display();
    };
    class SimpleCounter:public Count
    {
        public:
            SimpleCounter& SimpleCounter_increment();
    };
    class ExtendedCounter:public Count
    {
        public:
            ExtendedCounter(int cp_steper);
            ExtendedCounter& ExtendedCounter_increment();
            ExtendedCounter& ExtendedCounter_decrement();
    };
    class Serial
    {
        private:
            static int serial;
            int serial_number;
        public:
            Serial();
            void Display(); 
    };
}