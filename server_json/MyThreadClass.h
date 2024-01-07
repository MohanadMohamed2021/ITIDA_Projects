#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <map>
#include <algorithm>
#include <QTextStream>
#include "qtextensions.h"
#include <vector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QThread>
#include "DataBase.h"
#include <QProcess>
#include <QCryptographicHash>

class MyThreadClass:public QThread
{
    Q_OBJECT
public:
    /********The constructor********/
    explicit MyThreadClass(int ID, QObject *parent = 0);

    /**********Thread to handle connection***********/
    void run();

    /************Socket instance to handle connection***********/
    QTcpSocket *socket;

    /*************function to send respond***********/
    void server_SendMessage(QString data);

    /**************Function to select the reqired operation***********/
    void selectOperation(const QString message);

    /**************function to handle login request***********/
    void check_Login(QStringList parts);

    /*****************function to handle account number request with admin help*******/
    void getAccountNumber_Admin(QStringList parts);

    /*****************Function to handle logout request*************/
    void check_Logout(QStringList parts);

    /******************Function to handle account number request**********/
    void getAccountNumber(QStringList parts);

    /******************Function to handle account balance request************/
    void getAccountBalance(QStringList parts);

    /****************FUnction to handle data base request**********/
    void Get_DataBase(QStringList parts);

    /*****************Function to handle add new user request*********/
    void addNewUser(QStringList parts);

    /*****************Function to handle delete new user request*********/
    void deleteUser(QStringList parts);

    /*****************Function to handle update new user request*********/
    void updateUser(QStringList parts);

    /*****************Function to handle transfer money request*********/
    void Transfer(QStringList parts);

    /****************Function to handle withdraw money request**********/
    void Transaction_WithDraw(QStringList parts);

    /****************Function to handle deposite money request**********/
    void Transaction_Deposite(QStringList parts);

    /****************Function to handle transaction data base history request**********/
    void getTransaction_DataBase(QStringList parts);

    /*********************Function to encrypt data***************/
    QString decryptMessage(const QString &encryptedMessage, const QString &key);

    /*********************Function to decrypt data***************/
    QString encryptMessage(const QString &message, const QString &key);

    /********************Function to force logout**************/
    static void signal_helper();

private slots:
    void on_clientDataReady();          //slot connected to readyRead signal
    void on_clientDisconnected();       //slot connected to disconnect signal

private:
    std::pair<QString,QTcpSocket *> _socketList; //map to hold data of every socket in system
    int socketDescriptor;   //interger to hold socketDescriptor id;
    QTextStream qin;    //instance to scan input from user
    QTextStream qout;   //instance to print output to user
    QString _user_name;
    QProcess *python;
    QStringList args;
};

#endif // MYTCPSERVER_H
