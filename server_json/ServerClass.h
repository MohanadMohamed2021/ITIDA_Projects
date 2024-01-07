#ifndef THREADCLASS_H
#define THREADCLASS_H

#include <QObject>
#include <QTextStream>
#include "qtextensions.h"
#include <QTcpSocket>
#include "MyThreadClass.h"
#include "DataBase.h"
#include <QTimer>
#include <QProcess>

class ServerClass : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerClass(QObject *parent = nullptr);

    /***************this function will start the server************/
    void startServer();         //Function to start server
    QProcess* getBackUp_bash();  //Function to return the intialized instance of QProcess

protected:
    /*********this an override function used to connect with new clients***************/
   void incomingConnection(qintptr socketDescriptor);

public slots:
   void onTimeout();   //slots happens when timer time finished

private:
    QTextStream qin;     //instance of QTextStream to handle the input from use
    QTextStream qout;    //instance of QTextStream to handle the output to use
    qint32 _port;      //this variable will hold the port number
    //instance from data base class only to initialize the vectors when server started
    DataBase _dataBase;
    QProcess *BackUp_bash;  //Instance for backup
    QTimer BackUp;          //Instance for timer backup
};

#endif // THREADCLASS_H
