#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDebug>
#include <QThread>

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);
    void doWork();
    void setTime(quint32 cp_hours, quint32 cp_minutes, quint32 cp_seconds);
    void getData(quint32 *hours_now, quint32 *minutes_now, quint32 *seconds_now);

signals:
    void Display();
    void Buzzer();
private:
    quint32 hours;
    quint32 minutes;
    quint32 seconds;
};

#endif // TIMER_H
