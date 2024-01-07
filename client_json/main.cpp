#include <QCoreApplication>
#include "ClientClass.h"
#include "qtextensions.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ClientClass ClientClass;

    return a.exec();
}
