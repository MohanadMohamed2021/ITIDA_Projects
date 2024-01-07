#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QStyle>
#include <QMetaEnum>
#include <QDebug>
#include "qtextensions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDeviceController();
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_leIpAddress_textChanged(const QString &arg1)
{
    QHostAddress address(arg1);
    if (QAbstractSocket::IPv4Protocol == address.protocol())
    {
        ui->leIpAddress->setProperty("state", 1);
    }
    else
    {
        ui->leIpAddress->setProperty("state", 0);
    }
    style()->polish(ui->leIpAddress);
}

void MainWindow::on_pbConnect_clicked()
{
    if(_controller.isConnected())
    {
        _controller.socketDisconnect();
    }
    else
    {
        auto ip = ui->leIpAddress->text();
        auto port = ui->sbPort->value();
        _controller.connectToDevice(ip, port);
    }
}
void MainWindow::setDeviceController()
{
    connect(&_controller,&DeviceController::connected,this,&MainWindow::device_connected);
    connect(&_controller,&DeviceController::disconnected,this,&MainWindow::device_disconnected);
    connect(&_controller,&DeviceController::errorOccurred,this,&MainWindow::device_errorOccurred);
    connect(&_controller,&DeviceController::stateChanged,this,&MainWindow::device_stateChanged);
    connect(&_controller,&DeviceController::dataReady,this,&MainWindow::device_dataReady);
}

void MainWindow::device_connected()
{
    ui->lstConsole->addItem("Connect to device");
    ui->pbConnect->setText("Disconnect");
}

void MainWindow::device_disconnected()
{
    ui->lstConsole->addItem("Disconnect from device");
    ui->pbConnect->setText("connect");
}

void MainWindow::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    ui->lstConsole->addItem(metaEnum.valueToKey(error));
}

void MainWindow::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->lstConsole->addItem(metaEnum.valueToKey(state));
}

void MainWindow::on_pbClear_clicked()
{
    ui->lstConsole->clear();
}

void MainWindow::device_dataReady(QByteArray data,bool login,bool logout)
{
    if(login)
    {
        bool isChecked = ui->checkBox->isChecked();
        if(isChecked)
        {
           ui->tabWidget->setTabEnabled(2, true);
           ui->tabWidget->setTabEnabled(0, false);
        }
        else
        {
           ui->tabWidget->setTabEnabled(1, true);
           ui->tabWidget->setTabEnabled(0, false);
        }
    }
    else if(logout)
    {
        ui->tabWidget->setTabEnabled(0, true);
        ui->tabWidget->setTabEnabled(1, false);
        ui->tabWidget->setTabEnabled(2, false);
        ui->lstRecieveData->clear();
        QList<QLineEdit *> lineEdits = findChildren<QLineEdit *>();
        for (auto lineEdit: lineEdits)
        {
            if(lineEdit == (ui->leIpAddress))
            {
                continue;
            }
            lineEdit->clear();
        }
    }
    ui->lstRecieveData->addItem(QString(data.prepend(">> ")));
    ui->lstRecieveData->addItem("\n\n");
}

void MainWindow::on_pbClearRecievedData_clicked()
{
    ui->lstRecieveData->clear();
}


void MainWindow::on_pbLogin_clicked()
{
    _user_name=ui->leName->text();
    QString passward=ui->lePassward->text();
    QString message = QString("usrpass:%1:%2").arg(_user_name).arg(passward);
    _controller.socketSendData(message);
}


void MainWindow::on_pblogout_clicked()
{
    QString message = QString("logout:%1").arg(_user_name);
    _controller.socketSendData(message);
}


void MainWindow::on_pbHelp_clicked()
{
    _controller.socketSendData("help");
}


void MainWindow::on_pbGetACC_clicked()
{
    QString message = QString("acc:%1").arg(_user_name);
    _controller.socketSendData(message);
}


void MainWindow::on_pbBalance_clicked()
{
    QString Account_Number=ui->leAccBal->text();
    QString message = QString("bal:%1").arg(Account_Number);
    _controller.socketSendData(message);
}


void MainWindow::on_pbGetHistory_clicked()
{
    QString Account_Number=ui->leAccHistory->text();
    QString message = QString("history:%1").arg(Account_Number);
    _controller.socketSendData(message);
}


void MainWindow::on_pbWithdraw_clicked()
{
    QString Account_Number=ui->leAccWithdraw->text();
    QString amount=ui->leAccMoneyWithdraw->text();
    QString message = QString("withdraw:%1:%2").arg(Account_Number).arg(amount);
    _controller.socketSendData(message);
}


void MainWindow::on_pbDeposit_clicked()
{
    QString Account_Number=ui->leAccDeposit->text();
    QString amount=ui->leAccMoneyDeposit->text();
    QString message = QString("deposit:%1:%2").arg(Account_Number).arg(amount);
    _controller.socketSendData(message);
}


void MainWindow::on_pbTransfer_clicked()
{
    QString myAccountNumber=ui->leAccTransferY->text();
    QString hisAccountNumber=ui->leAccTransferH->text();
    QString amount=ui->leAccMoneyTRansfer->text();
    QString message = QString("transfer:%1:%2:%3").arg(myAccountNumber).arg(hisAccountNumber).arg(amount);
    _controller.socketSendData(message);
}


void MainWindow::on_pbGetAACC_clicked()
{
    QString username=ui->leUserName->text();
    QString message = QString("aacc:%1:%2").arg(_user_name).arg(username);
    _controller.socketSendData(message);
}


void MainWindow::on_pbBalanceA_clicked()
{
    QString Account_Number=ui->leAccBalA->text();
    QString message = QString("bal:%1").arg(Account_Number);
    _controller.socketSendData(message);
}


void MainWindow::on_pbGetHistoryA_clicked()
{
    QString Account_Number=ui->leAccHistoryA->text();
    QString message = QString("history:%1").arg(Account_Number);
    _controller.socketSendData(message);
}


void MainWindow::on_pbGetData_clicked()
{
    QString message = QString("data:%1").arg(_user_name);
    _controller.socketSendData(message);
}


void MainWindow::on_pbCreate_clicked()
{
    QString username=ui->leUserNameA->text();
    QString passward=ui->lePasswardA->text();
    QString full_name=ui->leFullA->text();
    QString age=ui->leAgeA->text();

    QString message = QString("add:%1:%2:%3:%4:%5").arg(_user_name).arg(username).arg(passward).arg(full_name).arg(age);
    _controller.socketSendData(message);
}


void MainWindow::on_pbDel_clicked()
{
    QString account_number=ui->leAccDel->text();
    QString message = QString("del:%1:%2").arg(_user_name).arg(account_number);
    _controller.socketSendData(message);
}


void MainWindow::on_pbUpdate_clicked()
{
    QString account_number=ui->leUerAccA->text();
    QString username=ui->leUserNameUA->text();
    QString passward=ui->lePasswardUA->text();
    QString full_name=ui->leFullUA->text();
    QString age=ui->leAgeUA->text();

    QString message=QString("update:%1:%2:%3:%4:%5:%6").arg(_user_name).arg(account_number)
                          .arg(username).arg(passward).arg(full_name).arg(age);
    _controller.socketSendData(message);
}

