#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "cellule.h"
#include<QIntValidator>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->idc->setValidator ( new QIntValidator(0, 100, this));
    ui->tableView->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);

}


void MainWindow::on_pushButton_ajouter1_clicked()
{
    int id=ui->idc->text().toInt();
    int nbre_det=ui->nbdet->text().toInt();
    int nbre_det_max=ui->nbdetmax->text().toInt();
    int nbre_lit=ui->nblit->text().toInt();



        Cellule C(id,nbre_det,nbre_det_max,nbre_lit);
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



void MainWindow::on_pushButton_supp1_clicked()
{
    int id  = ui->lineEdit_13->text().toInt();
        bool test = C1.supprimer(id);

        if (test){

     ui->tableView->setModel(C.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_pushButton_modifier1_clicked()
{

    int id=ui->lineEdit->text().toInt();
    int nbre_det=ui->lineEdit_2->text().toInt();
    int nbre_det_max=ui->lineEdit_3->text().toInt();
    int nbre_lit=ui->lineEdit_4->text().toInt();


    Cellule C(id,nbre_det,nbre_det_max,nbre_lit);
    bool test = C.modifier(id);

    if (test){

 ui->tableView->setModel(C.afficher());


        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

}
