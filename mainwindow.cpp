#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QDateEdit>
#include"delits.h"
#include "chart.h"
#include "criminels.h"
#include<QMediaPlayer>
#include<QFileDialog>
#include<QComboBox>
#include"charttype.h"
#include <QPrinter>
#include <QPrintDialog>
#include<QTextDocument>
#include<QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QPdfWriter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_delit1->setStyleSheet("gridline-color:red");
    ui->tab_delit1->horizontalHeader()->setStyleSheet("gridline-color:red");
    ui->tab_delit1->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");
    ui->tab_delit2->setStyleSheet("gridline-color:red");
    ui->tab_delit2->horizontalHeader()->setStyleSheet("gridline-color:red");
    ui->tab_delit2->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");
    ui->tab_criminel1->setStyleSheet("gridline-color:red");
    ui->tab_criminel1->horizontalHeader()->setStyleSheet("gridline-color:red");
    ui->tab_criminel1->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");
    ui->tab_delit1->setModel(D1.afficher());
    ui->tab_delit2->setModel(D1.afficher());
    ui->tab_criminel1->setModel(C1.afficher_c());
    QSqlQuery query;
       int numRows= 0;
       query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
       if(query.first())
           numRows = query.value(0).toInt();
       QString numRowsstr=QString::number(numRows);

ui->lineEdit_17->setText(numRowsstr);

mMediaPlayer = new QMediaPlayer (this);
connect(mMediaPlayer,&QMediaPlayer ::positionChanged,[&](qint64 pos){
    ui->avance->setValue(pos);
}    );
connect(mMediaPlayer,&QMediaPlayer::durationChanged,[&](qint64 dur) {
    ui->avance->setMaximum(dur);
});
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_6_clicked()
{
    int ID_DELIT=ui->ledelitid->text().toInt();
    QString TYPE_DELIT=ui->comboBox->currentText();


    QString DESCRIPTION_DELIT=ui->le_desc_delit->text();
    QDate DATE_DELIT=ui->dateEditdelit->date();
    int ID_CRIMINEL=ui->comboBox_2->currentText().toInt();
    Delits H(ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT,ID_CRIMINEL);
    bool test=H.ajouter();
    if (test){

        ui->tab_delit1->setModel(D1.afficher());
        ui->tab_delit2->setModel(D1.afficher());


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


    }





void MainWindow::on_supprimerPb_3_clicked()
{
    int ID_DELIT=ui->lineEdit_26->text().toInt();
    bool test =D1.supprimer(ID_DELIT);

    if (test){

     ui->tab_delit1->setModel(D1.afficher());
     ui->tab_delit2->setModel(D1.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
 QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_13_clicked()
{
    int ID_DELIT=ui->le_mid->text().toInt();
    QString TYPE_DELIT=ui->comboBox_3->currentText();
    QString DESCRIPTION_DELIT=ui->lineEdit_11->text();
     QDate DATE_DELIT=ui->dateEdit_3->date();
     int ID_CRIMINEL=ui->comboBox_2->currentText().toInt();

     Delits F(ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT,ID_CRIMINEL);
    bool test = F.modifier(ID_DELIT);

    if (test){

 ui->tab_delit1->setModel(F.afficher());
 ui->tab_delit2->setModel(F.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);



}

void MainWindow::on_PB_add_c_clicked()
{

        int ID_CRIMINEL=ui->lineEdit_id_c->text().toInt();
        QString NOM_CRIMINEL=ui->lineEdit_nom_c->text() ;
        QString PRENOM_CRIMINEL=ui->lineEdit_prenom_c->text();
        int AGE_CRIMINEL=ui->lineEdit_age_c->text().toInt();
        Criminels C1(ID_CRIMINEL,AGE_CRIMINEL,NOM_CRIMINEL,PRENOM_CRIMINEL);
        bool test=C1.ajouter_c();
        if (test){
            QSqlQuery query;
               int numRows= 0;
               query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
               if(query.first())
                   numRows = query.value(0).toInt();
               QString numRowsstr=QString::number(numRows);

        ui->lineEdit_17->setText(numRowsstr);
            ui->tab_criminel1->setModel(C1.afficher_c());


                QMessageBox::information(nullptr,QObject::tr("OK"),
                                         QObject::tr("Ajout effectué\n"
        "Click Cancel to exit"),QMessageBox::Cancel);


            }
            else
                QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);





}

void MainWindow::on_PB_DEL_C_clicked()
{
    int ID_CRIMINEL=ui->lineEdit_18->text().toInt();
    bool test =C1.supprimer_c(ID_CRIMINEL);

    if (test){
        QSqlQuery query;
           int numRows= 0;
           query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
           if(query.first())
               numRows = query.value(0).toInt();
           QString numRowsstr=QString::number(numRows);

    ui->lineEdit_17->setText(numRowsstr);
     ui->tab_criminel1->setModel(C1.afficher_c());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
 QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_PB_mod_c_clicked()
{
    int ID_CRIMINEL=ui->lineEdit_ID_cm->text().toInt();
    QString NOM_CRIMINEL=ui->lineEdit_nom_cm->text();
    QString PRENOM_CRIMINEL=ui->lineEdit_prenom_cm->text();
     int AGE_CRIMINEL=ui->lineEdit_age_cm->text().toInt();

     Criminels C1(ID_CRIMINEL,AGE_CRIMINEL,NOM_CRIMINEL,PRENOM_CRIMINEL);
    bool test = C1.modifier_c(ID_CRIMINEL);

    if (test){

 ui->tab_criminel1->setModel(C1.afficher_c());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_pushButton_12_clicked()
{
    QSqlQuery query;
    int ID_DELIT=ui->lineEdit_27->text().toInt();

    QString ID_DELITstr=QString::number(ID_DELIT);

    query.exec("SELECT * from DELITS WHERE ID_DELIT  ='"+ID_DELITstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tab_delit2;
     ui->tab_delit2->setStyleSheet("gridline-color:red");
     ui->tab_delit2->horizontalHeader()->setStyleSheet("gridline-color:red");
     ui->tab_delit2->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");

        view->setModel(model);
        ui->lineEdit_27->setText("");
}
void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query;
    int ID_CRIMINEL=ui->lineEdit_5->text().toInt();

    QString ID_CRIMINELstr=QString::number(ID_CRIMINEL);

    query.exec("SELECT * from CRIMINELS WHERE ID_CRIMINEL  ='"+ID_CRIMINELstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tab_criminel2;
     ui->tab_criminel2->setStyleSheet("gridline-color:red");
     ui->tab_criminel2->horizontalHeader()->setStyleSheet("gridline-color:red");
     ui->tab_criminel2->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");

        view->setModel(model);
        ui->lineEdit_ID_cm->setText("");
        ui->lineEdit_age_cm->setText("");
        ui->lineEdit_prenom_cm->setText("");
        ui->lineEdit_nom_cm->setText("");

}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query;
    int ID_CRIMINEL=ui->lineEdit_10->text().toInt();

    QString ID_CRIMINELstr=QString::number(ID_CRIMINEL);

    query.exec("SELECT * from CRIMINELS WHERE ID_CRIMINEL  ='"+ID_CRIMINELstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tableView_3;
     ui->tableView_3->setStyleSheet("gridline-color:red");
     ui->tableView_3->horizontalHeader()->setStyleSheet("gridline-color:red");
     ui->tableView_3->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");

        view->setModel(model);
        ui->lineEdit_ID_cm->setText("");
}

void MainWindow::on_pushButton_trier_clicked()
{

    QSqlQuery query;
    query.exec("SELECT * FROM DELITS ORDER BY TYPE_DELIT");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    QTableView *view =ui->tab_delit1;
    ui->tab_delit1->setStyleSheet("gridline-color:red");
    ui->tab_delit1->horizontalHeader()->setStyleSheet("gridline-color:red");
    ui->tab_delit1->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");

       view->setModel(model);
       ui->lineEdit_ID_cm->setText("");



}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.exec("SELECT * FROM DELITS ORDER BY DATE_DELIT");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    QTableView *view =ui->tab_delit1;
    ui->tab_delit1->setStyleSheet("gridline-color:red");
    ui->tab_delit1->horizontalHeader()->setStyleSheet("gridline-color:red");
    ui->tab_delit1->horizontalHeader()->setStyleSheet("border: 1px solid red;border-left: 1px solid red;font-weight:bold; color: red");

       view->setModel(model);
       ui->lineEdit_ID_cm->setText("");

}

void MainWindow::on_pushButton_5_clicked()
{
    chart chart;
    chart.setModal(true);
    chart.exec();
}
//music

void MainWindow::on_pushButton_ouvm_clicked()
{
   QString filename = QFileDialog :: getOpenFileName(this,"police");
   if (filename.isEmpty()) {return;}
   mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
   mMediaPlayer->setVolume(ui->volume->value());
   on_pushButton_play_clicked();
}

void MainWindow::on_pushButton_play_clicked()
{
    mMediaPlayer->play();
}

void MainWindow::on_pushButton_pause_clicked()
{
  mMediaPlayer->pause();
}

void MainWindow::on_pushButton_stop_clicked()
{
    mMediaPlayer->stop();
}

void MainWindow::on_pushButton_mute_clicked()
{
   if(ui->pushButton_mute->text()=="MUTE"){
    mMediaPlayer->setMuted(true);
    ui->pushButton_mute->setText("UNMUTE");
   }else {
       mMediaPlayer->setMuted(false);
       ui->pushButton_mute->setText("MUTE");
}
}

void MainWindow::on_volume_valueChanged(int value)
{
  mMediaPlayer->setVolume(value);
}

void MainWindow::on_PB_load_clicked()
{
    QSqlQuery query;
    query.exec("SELECT ID_CRIMINEL FROM CRIMINELS");
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    ui->comboBox_2->setModel(model);
        qDebug() <<(model->rowCount());



}

void MainWindow::on_pushButton_trier_2_clicked()
{    charttype charttype;
     charttype.setModal(true);
     charttype.exec();

}

void MainWindow::on_pushButton_4_clicked()
{




        int width = 0;
        int height = 0;

      ui->tab_criminel1->resizeColumnsToContents();
        ui->tab_criminel1->resizeRowsToContents();

        const int columnCnt = ui->tab_criminel1->model()->columnCount();
        for( int i = 0; i < columnCnt; ++i )
        {
            width += ui->tab_criminel1->columnWidth(i) ;
        }
       width=width*2;

        const int rowCnt = ui->tab_criminel1->model()->rowCount();
        for( int i = 0; i < rowCnt; ++i )
        {
            height += ui->tab_criminel1->rowHeight(i)  ;
        }
        height=height*2;

        ui->tab_criminel1->setFixedSize(width, height);

        QPrinter printer;

        ui->tab_criminel1->render(&printer);

        ui->tab_criminel1->setFixedSize(471, 321);






}
