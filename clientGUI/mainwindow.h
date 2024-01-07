#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QStyle>
#include <DeviceController.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_leIpAddress_textChanged(const QString &arg1);
    void on_pbClear_clicked();
    void on_pbConnect_clicked();
    void device_connected();
    void device_disconnected();
    void device_errorOccurred(QAbstractSocket::SocketError error);
    void device_stateChanged(QAbstractSocket::SocketState state);
    void device_dataReady(QByteArray data,bool login,bool logout);
    void on_pbClearRecievedData_clicked();
    void on_pbLogin_clicked();
    void on_pblogout_clicked();
    void on_pbHelp_clicked();
    void on_pbGetACC_clicked();
    void on_pbBalance_clicked();
    void on_pbGetHistory_clicked();
    void on_pbWithdraw_clicked();
    void on_pbDeposit_clicked();
    void on_pbTransfer_clicked();
    void on_pbGetAACC_clicked();
    void on_pbBalanceA_clicked();
    void on_pbGetHistoryA_clicked();
    void on_pbGetData_clicked();
    void on_pbCreate_clicked();
    void on_pbDel_clicked();
    void on_pbUpdate_clicked();

private:
    Ui::MainWindow *ui;
    DeviceController _controller;
    void setDeviceController();
    QString _user_name;
};
#endif // MAINWINDOW_H
