#include "chart.h"
#include "ui_chart.h"
#include "criminels.h"
#include <QSqlQuery>
#include <QSqlDriver>
chart::chart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chart)
{
    ui->setupUi(this);


    QSqlQuery query1;
       int numRows1= 0;
       query1.exec("SELECT COUNT(*) FROM CRIMINELS WHERE AGE_CRIMINEL<19 ");
       if(query1.first())
           numRows1 = query1.value(0).toInt();



       QSqlQuery query2;
            int numRows2= 0;
       query2.exec("SELECT COUNT(*) FROM CRIMINELS WHERE AGE_CRIMINEL>18 AND AGE_CRIMINEL<24");
       if(query2.first())
           numRows2 = query2.value(0).toInt();




       QSqlQuery query3;
             int numRows3= 0;
             query3.exec("SELECT COUNT(*) FROM CRIMINELS WHERE AGE_CRIMINEL>23 AND AGE_CRIMINEL<33");
             if(query3.first())
                 numRows3 = query3.value(0).toInt();



             QSqlQuery query4;
                    int numRows4= 0;
                    query4.exec("SELECT COUNT(*) FROM CRIMINELS WHERE AGE_CRIMINEL>31 AND AGE_CRIMINEL<46");
                    if(query4.first())
                        numRows4 = query4.value(0).toInt();



                      QSqlQuery query5;
                          int numRows5= 0;
                          query5.exec("SELECT COUNT(*) FROM CRIMINELS WHERE AGE_CRIMINEL>45");
                          if(query5.first())
                              numRows5 = query5.value(0).toInt();




    QPieSeries *series = new QPieSeries();
    series->append("Moins de 18 ans",numRows1);
    series->append("18-24",numRows2);
    series->append("25-32",numRows3);
    series->append("32-45",numRows4);
    series->append("46 et plus",numRows5);


    QChart *chartt = new QChart();
    chartt->addSeries(series);
    chartt->setTitle("Population carcérale par tranche d'âge");

    QChartView *chartview = new QChartView(chartt);
    chartview->setParent(ui->horizontalFrame);
        }

chart::~chart()
{
    delete ui;
}
