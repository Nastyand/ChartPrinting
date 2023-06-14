#include "datareading.h"

QMap<QString,double> SqlDataReading::GetData(QString filePath)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE"); // Для соединения с базой данных активизируем драйвер
    database.setDatabaseName(filePath);
    QMap<QString,double> data; // Создание объекта QMap

    // Осуществление соединения
    if (database.open()) {
        QStringList tables = database.tables();
        QSqlQuery query ("SELECT * FROM " + tables.first()); // Выполнение запроса, начиная с первой записи
        while (query.next()) { // Пока существует следующая запись
            data.insert(query.value(0).toString(), query.value(1).toDouble());// Добавление значения в объект data
        }
        qDebug()<< data.firstKey();// вывод 1 ключа для проверки
    }
    else {
        qDebug()<< "Ошибка в чтении файла ";
    }
    return data;
}
