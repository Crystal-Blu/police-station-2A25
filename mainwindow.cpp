#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "cellule.h"
#include<QIntValidator>
#include "detention.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->idc->setValidator ( new QIntValidator(1, 100, this));
    ui->tableView->setModel(C.afficher());
    ui->tableView_2->setModel(D.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ajouter1_clicked()
{
    int idcel=ui->idc->text().toInt();
    int nombre_det=ui->nbdet->text().toInt();
    int nombre_det_max=ui->nbdetmax->text().toInt();
    int nombre_lit=ui->nblit->text().toInt();



        Cellules C(idcel,nombre_det,nombre_det_max,nombre_lit);
        bool test = C.ajouter();

        if (test){

     ui->tableView->setModel(C.afficher());
     ui->tableView->setModel(C.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout effectué de la cellule avec succès\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_pushButton_modifier1_clicked()
{

    int idcel=ui->lineEdit->text().toInt();
    int nombre_det=ui->lineEdit_2->text().toInt();
    int nombre_det_max=ui->lineEdit_3->text().toInt();
    int nombre_lit=ui->lineEdit_4->text().toInt();


    Cellules C(idcel,nombre_det,nombre_det_max,nombre_lit);
    bool test = C.modifier(idcel);

    if (test){

 ui->tableView->setModel(C.afficher());


        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification de la cellule effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

}



void MainWindow::on_pushButton_supp1_clicked()
{
    int idcel  = ui->lineEdit_13->text().toInt();
        bool test = C1.supprimer(idcel);

        if (test){

     ui->tableView->setModel(C.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}





void MainWindow::on_pushButton_ajouter2_clicked()
{
    int iddet=ui->lineEdit_5->text().toInt();
    QDate date_entree=ui->dateEdit->date();
    QDate date_sortie=ui->dateEdit_2->date();
    QString raison=ui->lineEdit_8->text();
    int idcel=ui->lineEdit_9->text().toInt();
    int idp=ui->lineEdit_10->text().toInt();



        detentions D(iddet,date_entree,date_sortie,raison,idcel,idp);
        bool test = D.ajouter();

        if (test){

     ui->tableView_2->setModel(D.afficher());


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout de la detention effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modifier2_clicked()
{
    int iddet=ui->lineEdit_11->text().toInt();
    QDate date_entree=ui->dateEdit_3->date();
    QDate date_sortie=ui->dateEdit_4->date();
    QString raison=ui->lineEdit_15->text();
    int idcel=ui->lineEdit_17->text().toInt();
    int idp=ui->lineEdit_18->text().toInt();

           detentions D(iddet,date_entree,date_sortie,raison,idcel,idp);
           bool test = D.modifier(iddet);

           if (test){

        ui->tableView_2->setModel(D.afficher());


               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("Modification de la detention effectuée avec succés\n"
       "Click Cancel to exit"),QMessageBox::Cancel);


           }
           else
               QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification de la detention non effectuée.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_pushButton_supprimer2_clicked()
{
    int iddet  = ui->lineEdit_12->text().toInt();
        bool test = D1.supprimer(iddet);

        if (test){

     ui->tableView_2->setModel(D.afficher());


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression de la detention effectuée avec succès\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression de la detention non effectuée.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}
