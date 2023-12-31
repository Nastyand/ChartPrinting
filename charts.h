#ifndef CHARTS_H
#define CHARTS_H

#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>
#include <QChartView>
#include "datareading.h"

class Charts // Абстрактный класс для рисования диаграммы
{
public:
    virtual ~Charts() = default;
    void ChartDrawing(QMap<QString,double>, std::shared_ptr<QChartView>, int);
protected:
    virtual void CreateSeries(QMap<QString,double>,std::shared_ptr<QChartView>, int)=0;
    virtual void CreateAxes( std::shared_ptr<QChartView>);
    virtual void RemoveSeries (std::shared_ptr<QChartView>);
};

class BarCharts: public Charts // Кокретная реализация для столбчатой диаграммы
{
    void CreateSeries(QMap<QString,double>,std::shared_ptr<QChartView> chart, int);
};

class PieCharts: public Charts // Кокретная реализация для круговой диаграммы
{
    void CreateSeries(QMap<QString,double>,std::shared_ptr<QChartView> chart, int);
};


#endif // CHARTS_H
