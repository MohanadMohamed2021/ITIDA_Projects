#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    onFetchQuan("fruits");
    onFetchQuan("vegetables");
    onFetchQuan("canned_foods");
    onSetTab(1,false);
    onSetTab(2,false);
    onSetTab(3,false);
    onSetTab(4,false);
    onDisableButtons(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()
{
    onDisableButtons(false);
    QString category=ui->cbListItems->currentText();
    if(category=="Fruit")
    {
        onSetTab(1,true);
        onSetTab(0,false);
        onSetTab(2,false);
        onSetTab(3,false);
        onSetTab(4,false);
    }
    else if(category=="Vegetables")
    {
        onSetTab(2,true);
        onSetTab(0,false);
        onSetTab(1,false);
        onSetTab(3,false);
        onSetTab(4,false);
    }
    else if(category=="CannedFood")
    {
        onSetTab(3,true);
        onSetTab(0,false);
        onSetTab(1,false);
        onSetTab(2,false);
        onSetTab(4,false);
    }
}
void MainWindow::on_pbBack_clicked()
{
    onSetTab(0,true);
    onSetTab(1,false);
    onSetTab(2,false);
    onSetTab(3,false);
    onSetTab(4,false);
    onDisableButtons(true);
}
void MainWindow::on_pbBack_3_clicked()
{
    onSetTab(4,true);
    onSetTab(0,false);
    onSetTab(1,false);
    onSetTab(2,false);
    onSetTab(3,false);
}
void MainWindow::on_pbAddAdmin_clicked()
{
    QString type=ui->lineEdit_13->text();
    QString item=ui->lineEdit_14->text();
    QString price=ui->lineEdit_15->text();
    QString quantity=ui->leQuanAdd->text();
    QString str;
    QTextStream ss(&str);
    quint16 numPrice;
    quint16 numQuantity;
    ss<<price<<" "<<quantity;
    ss>>numPrice>>numQuantity;
    _device.addItem(type,item,numPrice);
    _device.addItemQuan(type,item,numQuantity);
    onFetchQuan(type);
}
void MainWindow::on_pbUpdateAdmin_clicked()
{
    QString type=ui->lineEdit_18->text();
    QString item=ui->lineEdit_19->text();
    QString price=ui->lineEdit_20->text();
    QTextStream ss(&price);
    quint16 numPrice;
    ss>>numPrice;
    _device.changePrice(type,item,numPrice);
}
void MainWindow::on_pbUpdateAdmin_2_clicked()
{
    QString type=ui->lineEdit_21->text();
    QString item=ui->lineEdit_22->text();
    QString quantity=ui->leQuanUpdate->text();
    QTextStream ss(&quantity);
    quint16 numQuantity;
    ss>>numQuantity;
    _device.changeQuantity(type,item,numQuantity);
}
void MainWindow::on_pbDeleteAdmin_clicked()
{
    QString type=ui->lineEdit_2000->text();
    QString item=ui->lineEdit_2001->text();
    _device.delItem(type,item);
    _device.delItemQuan(type,item);
    onFetchQuan(type);
}
void MainWindow::on_cbFruit_currentTextChanged(const QString &arg1)
{
    QString str;
    QVector<QJsonObject> v=_device.fetchItemsQuan();
    for(auto vv:v)
    {
        if(vv.contains(arg1))
        {
            str=vv[arg1].toString();
            ui->lineEdit->clear();
            ui->lineEdit->setText(str);
            break;
        }
    }
}
void MainWindow::on_cbVeg_currentTextChanged(const QString &arg1)
{
    QString str;
    QVector<QJsonObject> v=_device.fetchItemsQuan();
    for(auto vv:v)
    {
        if(vv.contains(arg1))
        {
            str=vv[arg1].toString();
            ui->leVeg->clear();
            ui->leVeg->setText(str);
            break;
        }
    }
}

void MainWindow::on_cbCan_currentTextChanged(const QString &arg1)
{
    QString str;
    QVector<QJsonObject> v=_device.fetchItemsQuan();
    for(auto vv:v)
    {
        if(vv.contains(arg1))
        {
            str=vv[arg1].toString();
            ui->leCan->clear();
            ui->leCan->setText(str);
            break;
        }
    }
}
void MainWindow::onDisableButtons(bool state)
{
    if(state==true)
    {
        ui->pbAddCart->setDisabled(true);
        ui->pbShowCart->setDisabled(true);
    }
    else
    {
        ui->pbAddCart->setDisabled(false);
        ui->pbShowCart->setDisabled(false);
    }
}
void MainWindow::onSetTab(quint16 tab,bool state)
{
   ui->twMarket->setTabEnabled(tab,state);
}
void MainWindow::onFetchQuan(QString type)
{
    QVector<QString> str=_device.fetchItems(type);
    if(type=="fruits")
    {
        ui->cbFruit->clear();
        for(int i=0;i<str.size();i++)
        {
            if(str[i]!="type")
            {
                ui->cbFruit->addItem(str[i]);
            }
        }
    }
    else if(type=="vegetables")
    {
        ui->cbVeg->clear();
        for(int i=0;i<str.size();i++)
        {
            if(str[i]!="type")
            {
                ui->cbVeg->addItem(str[i]);
            }
        }
    }
    else if(type=="canned_foods")
    {
        ui->cbCan->clear();
        for(int i=0;i<str.size();i++)
        {
            if(str[i]!="type")
            {
                ui->cbCan->addItem(str[i]);
            }
        }
    }
}



void MainWindow::on_pbAddCart_clicked()
{
    if(ui->twMarket->currentIndex()==1)
    {
        QString currentText=ui->cbFruit->currentText();
        QString quantity=ui->lineEdit->text();
        QString wanted=ui->leFruitWanted->text();
        if(wanted.toInt() <= quantity.toInt())
        {
            _cart.insert({currentText,wanted.toInt()});
        }
    }
    else if(ui->twMarket->currentIndex()==2)
    {
        QString currentText=ui->cbVeg->currentText();
        QString quantity=ui->leVeg->text();
        QString wanted=ui->leVegWanted->text();
        if(wanted.toInt() <= quantity.toInt())
        {
            _cart.insert({currentText,wanted.toInt()});
        }
    }
    else if(ui->twMarket->currentIndex()==3)
    {
        QString currentText=ui->cbCan->currentText();
        QString quantity=ui->leCan->text();
        QString wanted=ui->leCanWanted->text();
        if(wanted.toInt() <= quantity.toInt())
        {
            _cart.insert({currentText,wanted.toInt()});
        }
    }
}
void MainWindow::on_pbRemoveCart_clicked()
{
    QString removedItem=ui->leRemove->text();
    if(!_cart.empty())
    {
        if(_cart.count(removedItem))
        {
            _cart.erase(_cart.find(removedItem));
        }
    }
}
void MainWindow::on_pbShowCart_clicked()
{
    if (!_cart.empty())
    {
        for (std::pair<QString,quint16> pair:_cart)
        {
            QString itemText = pair.first + ": " + QString::number(pair.second);
            ui->lwItems->addItem(itemText);
        }
    }
}
void MainWindow::on_pbBack_2_clicked()
{
    qint32 sum=0;
    QVector<QJsonObject> v=_device.fetchItemsPrice();
    if(!_cart.empty())
    {
        for(std::pair<QString,quint16> pair:_cart)
        {
            for(QJsonObject vv:v)
            {
                if(vv.contains(pair.first))
                {
                    QString price=vv[pair.first].toString();
                    QTextStream ss(&price);
                    quint16 numPrice;
                    ss>>numPrice;
                    _cartPrice.insert({pair.first,numPrice});
                    qDebug()<<pair.first<<numPrice;
                    sum+=numPrice;
                    _device.calNewQuan(vv["type"].toString(),pair.first,pair.second);
                    if(vv["type"].toString()=="fruits")
                    {
                        on_cbFruit_currentTextChanged(pair.first);
                    }
                    else if(vv["type"].toString()=="vegetables")
                    {
                        on_cbVeg_currentTextChanged(pair.first);
                    }
                    else if(vv["type"].toString()=="canned_foods")
                    {
                        on_cbCan_currentTextChanged(pair.first);
                    }
                }
            }
        }
        qDebug()<<"******************************";
        ui->lcdTotalPrice->display(sum);
    }
}










