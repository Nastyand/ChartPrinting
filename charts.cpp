#include "charts.h"

void BarCharts::ChartDrawing(QMap<QString,double> data, std::shared_ptr<QChartView> chart)
{

    std::unique_ptr<QBarSeries >series(new QBarSeries()); // Создание серии пустых столбцов

    QMap<QString, double>::iterator i; // Создание итератора для перебора QMap
    for (i = data.begin(); i != data.end(); i++) // Цикл по данным
    {
        std::unique_ptr<QBarSet> set(new QBarSet(i.key())); // Создание набора столбцов с данным ключом
        set ->append(i.value()) ; // Добавление значения
        series->append(set.release()); //Добавление набора столбцов в серию
    }

    chart->chart()->removeAllSeries(); // Удаление всех объектов серии, добавленных на диаграмму
    chart->chart()->addSeries(series.release()); // Добавление серии к диаграмме
    chart->chart()->createDefaultAxes(); // Создание осей диаграммы
}

void PieCharts::ChartDrawing(QMap<QString,double> data, std::shared_ptr<QChartView> chart)
{

    std::unique_ptr<QPieSeries >series(new QPieSeries()); // Создание объекта серии круговых диаграмм

    QMap<QString, double>::iterator i; // Создание итератора для перебора QMap
    for (i = data.begin(); i != data.end(); i++) // Цикл по данным
    {
        std::unique_ptr<QPieSlice> slice(new QPieSlice(i.key(),i.value())); // Создание сектора с данным ключом и значением
        series->append(slice.release()); //Добавление сектора в серию
    }

    chart->chart()->removeAllSeries(); // Удаление всех объектов серии, добавленных на диаграмму
    chart->chart()->addSeries(series.release()); // Добавление серии к диаграмме
    chart->chart()->createDefaultAxes(); // Создание осей диаграммы
}
