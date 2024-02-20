#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&thread, &QThread::started, &timer, &Timer::doWork);
    connect(&thread, &QThread::finished, &thread, &QThread::deleteLater);
    connect(&timer, &Timer::Display,this,&MainWindow::onDisplay);
    connect(&timer, &Timer::Buzzer,this,&MainWindow::onBuzzer);
    timer.moveToThread(&thread);

    serialPort.setPortName("COM3");
    serialPort.setBaudRate(QSerialPort::Baud115200);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDisplay()
{
    quint32 h, m, s;
    timer.getData(&h, &m, &s);
    QString timeString = QString("%1:%2:%3").arg(h).arg(m).arg(s);
    qDebug()<<timeString;
    ui->textBrowser->setText(timeString);
}
void MainWindow::onBuzzer()
{
    if(serialPort.open(QIODevice::ReadWrite))
    {
        QByteArray data = "1";
        serialPort.write(data);
    }
    else
    {
        qDebug()<<"Can't open serial port....>_<";
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString time_onLineEdit = ui->lineEdit->text();
    QStringList parts = time_onLineEdit.split(":");
    if (parts.size() == 3)
    {
        quint32 h = parts[0].toInt();
        quint32 m = parts[1].toInt();
        quint32 s = parts[2].toInt();
        timer.setTime(h, m, s);
    }
    else
    {
        qDebug() << "Invalid time format";
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    thread.start();
}
