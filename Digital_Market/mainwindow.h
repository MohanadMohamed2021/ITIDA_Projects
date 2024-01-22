#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HandleDataBase.h"
#include <QTextStream>
#include <QDebug>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void onDisableButtons(bool state);
    void onSetTab(quint16 tab,bool state);
    void onFetchQuan(QString type);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_6_clicked();

    void on_pbBack_clicked();

    void on_pbBack_3_clicked();

    void on_pbAddAdmin_clicked();

    void on_pbUpdateAdmin_clicked();

    void on_pbDeleteAdmin_clicked();

    void on_pbUpdateAdmin_2_clicked();

    void on_cbFruit_currentTextChanged(const QString &arg1);

    void on_cbVeg_currentTextChanged(const QString &arg1);

    void on_cbCan_currentTextChanged(const QString &arg1);

    void on_pbAddCart_clicked();

    void on_pbRemoveCart_clicked();

    void on_pbShowCart_clicked();

    void on_pbBack_2_clicked();

private:
    Ui::MainWindow *ui;
    HandleDataBase _device;
    std::map<QString,quint16> _cart;
    std::map<QString,quint16> _cartPrice;
};
#endif // MAINWINDOW_H
