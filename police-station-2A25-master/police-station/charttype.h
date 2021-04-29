#ifndef CHARTTYPE_H
#define CHARTTYPE_H

#include <QDialog>
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include <QPieSeries>
#include "criminels.h"
#include"delits.h"
namespace Ui {
class charttype;
}

class charttype : public QDialog
{
    Q_OBJECT

public:
    explicit charttype(QWidget *parent = nullptr);
    ~charttype();

private:
    Ui::charttype *ui;
};

#endif // CHARTTYPE_H
