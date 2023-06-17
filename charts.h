#ifndef CHARTS_H
#define CHARTS_H

#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QChartView>
#include "datareading.h"

class ICharts // Абстрактный класс для рисования диаграммы
{
public:
    virtual ~ICharts() = default;
    virtual void ChartDrawing(QMap<QString,double>, std::shared_ptr<QChartView>) = 0;
};

class BarCharts: public ICharts // Кокретная реализация для столбчатой диаграммы
{
public:
    void ChartDrawing(QMap<QString,double>, std::shared_ptr<QChartView>);
};


#endif // CHARTS_H
