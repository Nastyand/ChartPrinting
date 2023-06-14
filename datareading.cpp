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


QMap<QString,double> JsonDataReading::GetData(QString filePath)
{

    QFile file(filePath); // Создание объекта для представления файла

    QMap<QString,double> data; // Создание объекта QMap

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) { // Проверка открывается ли файл
        QJsonDocument document = QJsonDocument::fromJson(file.readAll()); // Создание json-документа
        file.close(); // Закрытие файла

        QJsonObject object = document.object(); // Создание json-объекта из json-документа
        QListIterator<QString> iterator(object.keys()); // Создание итератора для обхода списка ключей объекта

        while (iterator.hasNext()) { // Пока существует следующий элемент
            data.insert(iterator.next(), object.value(iterator.next()).toDouble()); // Добавление значения в объект data
        }
        if (data.isEmpty()) {       // Проверка файла на пустоту
            qDebug()<< "Файл пуст ";
        }
         qDebug()<< data.firstKey();// вывод 1 ключа для проверки
    }
    else {
        qDebug()<< "Ошибка в чтении файла ";
    }

    return data;
}
