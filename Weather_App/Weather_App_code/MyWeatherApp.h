#ifndef MYWEATHERAPP_H
#define MYWEATHERAPP_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTcpSocket>
#include <QMetaEnum>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class MyWeatherApp : public QObject
{
    Q_OBJECT
public:
    explicit MyWeatherApp(QObject *parent = nullptr);
    void sendRequest(QString request);
public slots:
    void onDisconnected();
    void onReadyRead();
    void onStateChanged(QAbstractSocket::SocketState state);
    void onErrorOccurred(QAbstractSocket::SocketError error);
signals:
    void weatherData(double temp,double feels_like,double temp_min,double temp_max,
                     qint32 pressure,qint32 humidity,double speed,QString description);
private:
    QTcpSocket *_socket;

};

#endif // MYWEATHERAPP_H
