#include "charts.h"

void Charts::ChartDrawing(QMap<QString,double> data, std::shared_ptr<QChartView> chart, int limit)
{
    RemoveSeries (chart); // Удаление объектов серии
    CreateSeries(data,chart,limit); // Создание серии
    CreateAxes(chart);  // Добавление осей
}

void BarCharts::CreateSeries(QMap<QString,double> data,std::shared_ptr<QChartView> chart, int limit)
{
    std::unique_ptr<QBarSeries>series(new QBarSeries()); // Создание серии пустых столбцов

    QMap<QString, double>::iterator i; // Создание итератора для перебора QMap
    int j=0;
    for (i = data.begin(); i != data.end() && j<limit; i++,j++) // Цикл по данным
    {
        std::unique_ptr<QBarSet> set(new QBarSet(i.key())); // Создание набора столбцов с данным ключом
        set ->append(i.value()) ; // Добавление значения
        series->append(set.release()); //Добавление набора столбцов в серию
    }
    chart->chart()->addSeries(series.release()); // Добавление серии к диаграмме
}

void PieCharts::CreateSeries(QMap<QString,double> data,std::shared_ptr<QChartView> chart, int limit)
{

    std::unique_ptr<QPieSeries>series(new QPieSeries()); // Создание объекта серии круговых диаграмм

    QMap<QString, double>::iterator i; // Создание итератора для перебора QMap
    int j=0;
    for (i = data.begin(); i != data.end() && j< limit; i++,j++) // Цикл по данным
    {
        std::unique_ptr<QPieSlice> slice(new QPieSlice(i.key(),i.value())); // Создание сектора с данным ключом и значением
        series->append(slice.release()); //Добавление сектора в серию
    }
    chart->chart()->addSeries(series.release()); // Добавление серии к диаграмме
}


void Charts::CreateAxes(std::shared_ptr<QChartView> chart)
{

    chart->chart()->createDefaultAxes(); // Создание осей диаграммы
}

void Charts::RemoveSeries (std::shared_ptr<QChartView> chart)
{
     chart->chart()->removeAllSeries(); // Удаление всех объектов серии, добавленных на диаграмму
}
