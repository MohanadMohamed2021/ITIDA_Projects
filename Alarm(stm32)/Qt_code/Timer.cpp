#include "Timer.h"

Timer::Timer(QObject *parent)
    : QObject{parent}, hours(0), minutes(0), seconds(0)
{}

void Timer::doWork()
{
    while(true)
    {
        if ((seconds > 0) || (minutes > 0) || (hours > 0))
        {
            if ((seconds == 0) && (minutes > 0))
            {
                seconds += 60;
                minutes--;
            }
            if ((minutes == 0) && (hours > 0))
            {
                minutes += 60;
                hours--;
            }
            seconds--;
        }
        else
        {
            qDebug() << "Time is already out.......>_";
            emit Buzzer();
        }
        emit Display();
        QThread::sleep(1);
    }
}

void Timer::setTime(quint32 cp_hours, quint32 cp_minutes, quint32 cp_seconds)
{
    hours = cp_hours;
    minutes = cp_minutes;
    seconds = cp_seconds;
}

void Timer::getData(quint32 *hours_now, quint32 *minutes_now, quint32 *seconds_now)
{
    *hours_now = hours;
    *minutes_now = minutes;
    *seconds_now = seconds;
}
