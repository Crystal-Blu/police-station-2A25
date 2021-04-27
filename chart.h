#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include<QBarSet>
#include<QBarSeries>
#include "criminels.h"
#include"delits.h"

namespace Ui {
class chart;
}

class chart : public QDialog
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = nullptr);
    ~chart();

private:
    Ui::chart *ui;
};

#endif // CHART_H
