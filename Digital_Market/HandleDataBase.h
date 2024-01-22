#ifndef HANDLEDATABASE_H
#define HANDLEDATABASE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QFile>

class HandleDataBase : public QObject
{
    Q_OBJECT
public:
    explicit HandleDataBase(QObject *parent = nullptr);
    bool addItem(QString type,QString item,quint16 price);
    bool addItemQuan(QString type,QString item,quint16 price);
    bool delItem(QString type,QString item);
    bool delItemQuan(QString type,QString item);
    bool changePrice(QString type,QString item,quint16 price);
    bool changeQuantity(QString type,QString item,quint16 quantity);
    bool calNewQuan(QString type,QString item,quint16 quantity);
    QVector<QString> fetchItems(QString type);
    QVector<QJsonObject> fetchItemsQuan();
    QVector<QJsonObject> fetchItemsPrice();
signals:

private:
    QVector<QJsonObject> _dataBase;
    QVector<QString> _dataBaseQuan;
    QVector<QJsonObject> quantity;
    QVector<QJsonObject> price;
    QString _path;
    QString _pathQuan;
};

#endif // HANDLEDATABASE_H
