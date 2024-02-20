#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <Timer.h>
#include <QString>
#include <QSerialPort>

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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onDisplay();
    void onBuzzer();

private:
    Ui::MainWindow *ui;
    Timer timer;
    QThread thread;
    QSerialPort serialPort;
};

#endif // MAINWINDOW_H
