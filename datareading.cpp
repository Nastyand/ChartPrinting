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
    }
    else {
        QMessageBox::information(nullptr, "Ошибка", "Файл не читается");
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
            QString key=iterator.next();
            double value =object.value(key).toDouble();
            data.insert(key, value); // Добавление значения в объект data
        }
        if (data.isEmpty()) {       // Проверка файла на пустоту
            QMessageBox::information(nullptr, "Ошибка", "Файл пуст");
        }
    }
    else {
        QMessageBox::information(nullptr, "Ошибка", "Файл не читается");
    }
    return data;
}

QMap<QString,double> CsvDataReading::GetData(QString filePath)
{

    QFile file(filePath); // Создание объекта для представления файла

    QMap<QString,double> data; // Создание объекта QMap

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) { // Проверка открывается ли файл

        QTextStream text(&file); //Создание потока для извлечения данных из файла

        while (!text.atEnd()) // Считывание данных до конца файла
        {
            QString line = text.readLine(); // Чтение одной строки
            QStringList parts = line.split(";"); // Разделение строки по ';'
            data.insert(parts[0], parts[1].toDouble()); // Добавление значения в объект data
        }

        file.close(); // Закрытие файла
        if (data.isEmpty()) { // Проверка файла на пустоту
            QMessageBox::information(nullptr, "Ошибка", "Файл пуст");
        }
    }
    else {
        QMessageBox::information(nullptr, "Ошибка", "Файл не читается");
    }
    return data;
}
