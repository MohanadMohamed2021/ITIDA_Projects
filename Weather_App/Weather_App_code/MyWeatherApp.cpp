#include "MyWeatherApp.h"

#define URL "api.openweathermap.org"
#define PORT 80

MyWeatherApp::MyWeatherApp(QObject *parent)
    : QObject{parent}
{
    _socket = new QTcpSocket(this);

    connect(_socket,&QTcpSocket::disconnected,this,&MyWeatherApp::onDisconnected);
    connect(_socket,&QTcpSocket::readyRead,this,&MyWeatherApp::onReadyRead);
    connect(_socket,&QTcpSocket::stateChanged,this,&MyWeatherApp::onStateChanged);
    connect(_socket,&QTcpSocket::errorOccurred,this,&MyWeatherApp::onErrorOccurred);

    _socket->connectToHost(URL,PORT);
    _socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    if(_socket->waitForConnected())
    {
        qDebug()<<"||-------------------||\n"
                  "||-----Connected-----||\n"
                  "||---Successfully----||\n"
                  "||-------------------||\n";
    }
    else
    {
        qDebug()<<"Failed to connect.......>_<";
    }
}

void MyWeatherApp::onDisconnected()
{
    qDebug()<<"Disconnected from the website.............T_T";
}
void MyWeatherApp::sendRequest(QString request)
{
    if(_socket->isOpen())
    {
        _socket->write(request.toUtf8());
    }
    else
    {
        qDebug()<<"Failed to send data ==> socket close......>_<";
    }
}
void MyWeatherApp::onReadyRead()
{
    QByteArray response = _socket->readAll();
    qDebug()<<response;
    QString responseSTR = QString(response);
    qint32 size = responseSTR.split(":")[6].split("\r")[0].toInt();
    QString temp_1 = responseSTR.right(size);
    QJsonDocument Doc = QJsonDocument::fromJson(temp_1.toUtf8());
    qDebug()<<Doc;
    if(!Doc.isNull())
    {
        qDebug()<<"Valid response........^_^";

        QJsonObject rootObject = Doc.object();

        QJsonObject mainObject = rootObject["main"].toObject();
        double temp = mainObject["temp"].toDouble();
        double feels_like = mainObject["feels_like"].toDouble();
        double temp_min = mainObject["temp_min"].toDouble();
        double temp_max = mainObject["temp_max"].toDouble();
        double pressure = mainObject["pressure"].toInt();
        double humidity = mainObject["humidity"].toInt();
        qDebug()<<temp<<" "<<feels_like<<" "<<temp_max<<" "<<temp_min<<" "<<pressure<<" "<<humidity;

        QJsonObject windObject = rootObject["wind"].toObject();
        double speed = windObject["speed"].toDouble();

        QJsonArray weatherArray = rootObject["weather"].toArray();
        QString description;
        for(qint32 i=0 ; i<weatherArray.size() ; i++)
        {
            QJsonObject obj = weatherArray[i].toObject();
            description = obj["description"].toString();
        }
        emit weatherData(temp,feels_like,temp_min,temp_max,pressure,humidity,speed,description);
    }
    else
    {
        qDebug()<<"Invalid json format.......>_<";
    }
}
void MyWeatherApp::onStateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug()<<"Socket State ==> "<<metaEnum.valueToKey(state);
    if(state == QAbstractSocket::SocketState::ClosingState)
    {
        _socket->close();
    }
}
void MyWeatherApp::onErrorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug()<<"Socket State ==> "<<metaEnum.valueToKey(error);
}
