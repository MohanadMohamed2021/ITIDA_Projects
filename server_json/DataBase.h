#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include "qtextensions.h"
#include <random>
#include <chrono>
#include <QDate>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

class DataBase : public QObject
{
    Q_OBJECT
public:
    /************this the constructor of the class************/
    explicit DataBase(QObject *parent = nullptr);

    /************this a getter function to get the data inside data base file************/
    QVector<QJsonObject> get_DataBase();

    /************this a getter function to get the data inside data base Transaction file************/
    QVector<QJsonObject> get_Transaction_DataBase();

    /************this a function to add new data of new client of the bank into data base file************/
    bool add_DataBase(const QString usr,const QString pass,const QString fullname,const QString age);

    /************this a function to change the state of log of the user/admin in data base file************/
    void set_Login(const QString user_name,const QString state);

    /************this a function to erase a user from data base file************/
    bool deleteUser(const QString accountNumber);

    /************this a function to update the data inside data base  file************/
    bool update_DataBase(const QString account_number,const QString usr,const QString pass,
                        const QString full_name,const QString age);

    /************this a function to update the data inside data base Transaction file************/
    bool update_Transaction(const QString accountNumber,const QString transaction,QString state);

    /************this a function to update the data inside data base Transaction file and data base file************/
    bool moneyTransfer(const QString accountNumberFrom,const QString accountNumberTo,
                       const QString amount_InFrom,const QString amount_InTo,const QString amount);

    /************this a function to update the data inside data base Transaction file and data base file************/
    bool moneyTransaction_WithDraw(const QString accountNumber,const QString myMoney,const QString transaction);

    /************this a function to update the data inside data base Transaction file and data base file************/
    bool moneyTransactionPut(const QString accountNumber,const QString myMoney,const QString transaction);

    /*****************this function used to update the vector by the data base Transaction file*************/
    void on_Init_DataBase();

    /*****************this function used to update the vector by the data base file*************/
    void on_Init_Transaction_DataBase();

    /*******************Generate unique account number****************/
    QString Generate_AccountNumber();

private:
    QVector<QJsonObject> _dataBase;      //vector used to hold the data base file info
    QVector<QJsonObject> _dataBase_Transaction;   //vector used to hold the data base Transaction file info
    QTextStream qin;     //instance of QTextStream to handle the input from use
    QTextStream qout;    //instance of QTextStream to handle the output to use
    QString _pathData;      //this variable will hold the path to data base file
    QString _pathDataTrans;  //this variable will hold the path to data base Transaction file
};

#endif // DATABASE_H
