#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <MyWeatherApp.h>
#include <QDebug>
#include <QString>

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
    void onWeatherData(double temp,double feels_like,double temp_min,double temp_max,
                       qint32 pressure,qint32 humidity,double speed,QString description);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
