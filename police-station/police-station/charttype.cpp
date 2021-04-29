#include "charttype.h"
#include "ui_charttype.h"
#include <QSqlQuery>
#include <QSqlDriver>
#include"delits.h"
charttype::charttype(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::charttype)
{
    ui->setupUi(this);


    QBarSet *set0 = new QBarSet("Delit");
    QBarSet *set1 = new QBarSet("Contravention");
    QBarSet *set2 = new QBarSet("Crime");




    QSqlQuery query1;
       int numRows1= 0;
       query1.exec("SELECT COUNT(*) FROM DELITS WHERE TYPE_DELIT='Delit'");
       if(query1.first())
           numRows1 = query1.value(0).toInt();





       QSqlQuery query2;
          int numRows2= 0;
          query2.exec("SELECT COUNT(*) FROM DELITS WHERE TYPE_DELIT='Contravention'");
          if(query2.first())
              numRows2 = query2.value(0).toInt();


          QSqlQuery query3;
             int numRows3= 0;
             query3.exec("SELECT COUNT(*) FROM DELITS WHERE TYPE_DELIT='Crime'");
             if(query3.first())
                 numRows3 = query3.value(0).toInt();






    *set0 << numRows1 << 0 <<0 ;
    *set1 <<0 << numRows2 <<0 ;
    *set2 <<0 << 0 <<numRows3;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

 QChart *chart = new QChart();
 chart->addSeries(series);
 chart->setTitle("charte de type");
 chart->setAnimationOptions(QChart::SeriesAnimations);
 QStringList categories;
 categories <<"Délit" << "Contravention" << "Crime" ;
 QBarCategoryAxis *axis = new QBarCategoryAxis();
 axis->append(categories);
 chart->createDefaultAxes();
 chart->setAxisX(axis,series);
 QChartView *chartView =new QChartView(chart);
 chartView->setParent(ui->horizontalFrame);




}
charttype::~charttype()
{
    delete ui;
}
