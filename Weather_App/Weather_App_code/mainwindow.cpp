#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString imagePath = QCoreApplication::applicationDirPath() + "/image.jpg";
    QPixmap image(imagePath);
    ui->label->setPixmap(image);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString city = ui->lineEdit->text();
    QString request = QString("GET /data/2.5/weather?q=%1,uk&units=metric&appid=6541ce36e7bdc60ee9ee6c46ed58fd21 HTTP/1.1\r\n"
                              "Host: api.openweathermap.org\r\n"
                              "Connection: close\r\n"
                              "\r\n").arg(city);
    MyWeatherApp *weather;
    weather = new MyWeatherApp(this);
    connect(weather,&MyWeatherApp::weatherData,this,&MainWindow::onWeatherData);
    weather->sendRequest(request);
}

void MainWindow::onWeatherData(double temp,double feels_like,double temp_min,double temp_max,
                   qint32 pressure,qint32 humidity,double speed,QString description)
{
    ui->label_6->setText(QString::number(temp));
    ui->label_8->setText(QString::number(feels_like));
    ui->label_10->setText(QString::number(temp_min));
    ui->label_18->setText(QString::number(temp_max));
    ui->label_16->setText(QString::number(pressure));
    ui->label_20->setText(QString::number(humidity));
    ui->label_12->setText(QString::number(speed));
    ui->label_14->setText(description);
}
