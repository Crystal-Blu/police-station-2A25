#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QDateEdit>
#include"delits.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_delit1->setModel(D1.afficher());
    ui->tab_delit2->setModel(D1.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_6_clicked()
{
    int ID_DELIT=ui->ledelitid->text().toInt();
    QString TYPE_DELIT=ui->lineEdit_typedelit->text() ;
    QString DESCRIPTION_DELIT=ui->le_desc_delit->text();
    QDate DATE_DELIT=ui->dateEditdelit->date();
    Delits H(ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT);
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
    QString TYPE_DELIT=ui->lineEdit_12->text();
    QString DESCRIPTION_DELIT=ui->lineEdit_11->text();
     QDate DATE_DELIT=ui->dateEdit_3->date();

     Delits F(ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT);
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
