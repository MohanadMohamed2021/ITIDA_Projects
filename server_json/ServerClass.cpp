#include "ServerClass.h"
#define TIME_FOR_BACKUP  86400000
#define PORT 12345

ServerClass::ServerClass(QObject *parent)
    : QTcpServer{parent},qin(stdin),qout(stdout),_port(PORT)
{
    //create timer to execute backup function
    BackUp.setInterval(TIME_FOR_BACKUP);
    connect(&BackUp,&QTimer::timeout,this,&ServerClass::onTimeout);
    BackUp.start();

    //Create QProcess to execute bash script
    BackUp_bash=new QProcess(this);
    QString scriptPath = "/home/mohanad/repo/ITIDA_Projects/bashScript.sh";
    QString gitRepoPath = "/home/mohanad/repo/ITIDA_Projects/";
    BackUp_bash->setWorkingDirectory(gitRepoPath);
    BackUp_bash->setProgram("bash");
    BackUp_bash->setArguments({scriptPath});
}

void ServerClass::onTimeout()
{
    BackUp_bash->start();
    if (BackUp_bash->waitForFinished())
    {
        qDebug() << "Script execution finished:";
        qDebug() << BackUp_bash->readAllStandardOutput();
    }
    else
    {
        qDebug() << "Script execution failed:";
        qDebug() << BackUp_bash->errorString();
    }
}
/***************this function will start the server************/
void ServerClass::startServer()
{
    if(this->listen(QHostAddress::Any,_port)) //check if the sever can listen to the port
    {
        qDebug() << ">> Server started.........\n";
        _dataBase.on_Init_DataBase();     //initialize the DataBase vector with data base file

        _dataBase.on_Init_Transaction_DataBase();   //initialize the DataBase vector with data base Transaction file

        MyThreadClass::signal_helper();  //Force logout on every client

    }
    else
    {
        qDebug() << ">> Server hasn't started.......\n";
    }
}

/*********this an override function used to connect with new clients***************/
void ServerClass::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << "-> connecting..";      //print socketDescriptor of the  up coming client

    MyThreadClass *thread = new MyThreadClass(socketDescriptor,this); //create instance of MyThreadClass and initialize it socketDescriptor

    //connect finish signal to slot deleteLater to ensure the automatic delete of the QThread instance
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();  //here the thread start to handle the data of new client
}
QProcess* ServerClass::getBackUp_bash()
{
    return BackUp_bash;
}
