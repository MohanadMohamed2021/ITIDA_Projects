#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QDebug>
#include <QString>
#include <QTcpSocket>
#include <QTextStream>
#include <QMetaEnum>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>


class ClientClass: public QObject
{
    Q_OBJECT

public:
    explicit ClientClass(QObject *parent = 0);

    //Function to break connection when needed
    void socketDisconnect();

    /***************Function to handle and forward the comming message***********/
    void messageHandler(QString message);

    /***************Function to handle desired operation*************/
    void operations();

    /*****************Function to send requests**************/
    void sendMessage(const QString &str);

    /*******Function to send login request**************/
    void login();

    /********Function to handle logout request**************/
    void logout();

    /********Function to send request to get account number********/
    void getAccountNumber();

    /********Function to send request to get account number with admin help********/
    void getAccountNumber_Admin();

    /*************Function to request to get account balance***********/
    void getAccountBalane();

    /*************Function to send request to ger bank data***********/
    void getBankData();

    /*************Function to send request to add new member***********/
    void addNewUser();

    /*************Function to send request to delete member******************/
    void deleteUser();

    /***********Function to send request to update user data************/
    void updateUser();

    /**************Function to send request to transfer money*************/
    void moneyTransfer();

    /**************Function to send request to withdraw money*************/
    void moneyWithdraw();

    /**************Function to send request to deposite money*************/
    void moneyDeposit();

    /**************Function to send request to deposite money*************/
    void moneyTransHistory();

    //function to clear terminal
    void clearTerminal();

    QString encryptMessage(const QString &message, const QString &key);

    QString decryptMessage(const QString &encryptedMessage, const QString &key);
private slots:
    /***********Slot to handle if device disconnected************/
    void onDevice_Disconnected();

    /********************Slot to handle when error take place************/
    void onDevice_ErrorOccurred(QAbstractSocket::SocketError error);

    /*******************Slot to handle any change of the connection state***************/
    void onDevice_StateChanged(QAbstractSocket::SocketState state);

    /**************Slot to handle the comming respond from server**************/
    void onDevice_DataReady();

private:
    QTcpSocket *_socket;
    qint32 _port;
    QString _ip;
    QTextStream qin;
    QTextStream qout;
    bool login_flag;
    QString _user_name;
    quint32 trials;
};

#endif // MYTCPCLIENT_H
