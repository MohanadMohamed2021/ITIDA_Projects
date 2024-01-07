#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    void connectToDevice(QString ip,qint16 port);
    QAbstractSocket::SocketState GetState();
    bool isConnected();
    void socketDisconnect();
    void socketSendData(QString str);
    void messageHandler(QString message);
    QString encryptMessage(const QString &message, const QString &key);
    QString decryptMessage(const QString &encryptedMessage, const QString &key);
signals:
    void connected();
    void disconnected();
    void errorOccurred(QAbstractSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void dataReady(QByteArray data,bool login,bool logout);
private slots:
    void socket_stateChanged(QAbstractSocket::SocketState state);
    void socket_readyRead();
private:
    QTcpSocket _socket;
    QString _ip;
    qint16 _port;
};

#endif // DEVICECONTROLLER_H
