#ifndef DATAREADING_H
#define DATAREADING_H
#include <QString>
#include <QtSql>
#include <QDebug>
#include <QMap>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class IDataReading// Абстрактный класс для чтения данных
{
public:
    virtual ~IDataReading()=default;
    virtual QMap<QString,double> GetData(QString filePath)=0;
};

class SqlDataReading: public IDataReading // Конкретная реализация для sql
{
public:
    QMap<QString,double> GetData(QString filePath);// Метод, возвращающий данные в формате ключ-значение
};

class JsonDataReading: public IDataReading // Конкретная реализация для json
{
public:
    QMap<QString,double> GetData(QString filePath);// Метод, возвращающий данные в формате ключ-значение
};
#endif // DATAREADING_H
