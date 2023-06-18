#ifndef DATAREADING_H
#define DATAREADING_H
#include <QString>
#include <QtSql>
#include <QMap>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>

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

class CsvDataReading: public IDataReading // Конкретная реализация для csv
{
public:
    QMap<QString,double> GetData(QString filePath);// Метод, возвращающий данные в формате ключ-значение
};

class DataReader // Класс-контекст для создания объкта, хранит ссылку на объект конкретной стратегии
{
    std::shared_ptr<IDataReading> data;
public:
    DataReader(std::shared_ptr<IDataReading> d):data(d){}
    QMap<QString,double> GetData(QString filePath) // Метод, возвращающий данные в формате ключ-значение
    {
        return data->GetData(filePath);
    }
};

#endif // DATAREADING_H
