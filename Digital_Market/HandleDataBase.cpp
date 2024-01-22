#include "HandleDataBase.h"

HandleDataBase::HandleDataBase(QObject *parent)
    : QObject{parent},_path("../Digital_Market/items.json"),_pathQuan("../Digital_Market/item_quantity.json")
{

}

bool HandleDataBase::addItem(QString type,QString item,quint16 price)
{
    QFile file(_path);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"]==type)
                {
                    obj.insert(item,QString::number(price));
                    dataArray[i]=obj;
                    break;
                }
            }
            file.resize(0);
            file.write(QJsonDocument(dataArray).toJson());
            file.close();
            return true;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
            return false;
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
        return false;
    }
}
bool HandleDataBase::addItemQuan(QString type,QString item,quint16 quantity)
{
    QFile file(_pathQuan);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"]==type)
                {
                    obj.insert(item,QString::number(quantity));
                    dataArray[i]=obj;
                    break;
                }
            }
            file.resize(0);
            file.write(QJsonDocument(dataArray).toJson());
            file.close();
            return true;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
            return false;
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
        return false;
    }
}
bool HandleDataBase::delItem(QString type,QString item)
{
    QFile file(_path);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"]==type)
                {
                    obj.remove(item);
                    dataArray[i]=obj;
                }
            }
            file.resize(0);
            file.write(QJsonDocument(dataArray).toJson());
            file.close();
            return true;
        }
        {
            qDebug()<<"Invalid Json Document........>_<";
            return false;
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
        return false;
    }
}
bool HandleDataBase::delItemQuan(QString type,QString item)
{
    QFile file(_pathQuan);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"]==type)
                {
                    obj.remove(item);
                    dataArray[i]=obj;
                }
            }
            file.resize(0);
            file.write(QJsonDocument(dataArray).toJson());
            file.close();
            return true;
        }
        {
            qDebug()<<"Invalid Json Document........>_<";
            return false;
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
        return false;
    }
}
bool HandleDataBase::changePrice(QString type,QString item,quint16 price)
{
    QFile file(_path);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"]==type)
                {
                    if(obj.contains(item))
                    {
                        obj[item]=QString::number(price);
                        dataArray[i]=obj;
                        break;
                    }
                }
            }
            file.resize(0);
            file.write(QJsonDocument(dataArray).toJson());
            file.close();
            return true;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
            return false;
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
        return false;
    }
}
bool HandleDataBase::changeQuantity(QString type,QString item,quint16 quantity)
{
    QFile file(_pathQuan);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"]==type)
                {
                    if(obj.contains(item))
                    {
                        obj[item]=QString::number(quantity);
                        dataArray[i]=obj;
                        break;
                    }
                }
            }
            file.resize(0);
            file.write(QJsonDocument(dataArray).toJson());
            file.close();
            return true;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
            return false;
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
        return false;
    }
}
bool HandleDataBase::calNewQuan(QString type,QString item,quint16 quantity)
{
    int newQuantity;
    QFile file(_pathQuan);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"]==type)
                {
                    if(obj.contains(item))
                    {
                        QString exsistQuantity=obj[item].toString();
                        QTextStream ss(&exsistQuantity);
                        quint16 numExsistQuantity;
                        ss>>numExsistQuantity;
                        newQuantity = numExsistQuantity - quantity;
                        obj[item]=QString::number(newQuantity);
                        dataArray[i]=obj;
                        break;
                    }
                }
            }
            file.resize(0);
            file.write(QJsonDocument(dataArray).toJson());
            file.close();
            return true;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
            return false;
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
        return false;
    }
}
QVector<QString> HandleDataBase::fetchItems(QString type)
{
    _dataBaseQuan.clear();
    QFile file(_pathQuan);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        file.close();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                if(obj["type"].toString()==type)
                {
                    QList<QString> keys = obj.keys();
                    for (const QString& key : keys)
                    {
                        _dataBaseQuan.push_back(key);
                    }
                    keys.clear();
                }
            }
            return _dataBaseQuan;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
    }
}
QVector<QJsonObject> HandleDataBase::fetchItemsQuan()
{
    quantity.clear();
    QFile file(_pathQuan);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        file.close();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                quantity.push_back(obj);
            }
            return quantity;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
    }
}
QVector<QJsonObject> HandleDataBase::fetchItemsPrice()
{
    price.clear();
    QFile file(_path);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray data=file.readAll();
        file.close();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            QJsonArray dataArray=doc.array();
            for(int i=0;i<dataArray.size();i++)
            {
                QJsonObject obj=dataArray[i].toObject();
                price.push_back(obj);
            }
            return price;
        }
        else
        {
            qDebug()<<"Invalid Json Document........>_<";
        }
    }
    else
    {
        qDebug()<<"Cant open data base file........>_<";
    }
}
