#include <QCoreApplication>
#include "ServerClass.h"
#include "MyThreadClass.h"
#include <csignal>
#include <unistd.h>
#include <QDebug>

void signalHandler(int signum)
{
    qDebug() << "Interrupt signal (" << signum << ") received.\n";
    MyThreadClass::signal_helper();
    ServerClass signalHandler;
    QProcess *BackUp_bash=signalHandler.getBackUp_bash();
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
    exit(signum);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    signal(SIGTERM, signalHandler);  //connect server application with signal handler
    ServerClass server;
    server.startServer(); //start the server
    return a.exec();
}
