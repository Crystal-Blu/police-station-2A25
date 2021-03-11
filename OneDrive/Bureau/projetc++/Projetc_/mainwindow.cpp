#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citoyen.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QDateEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_supp->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_supp_2->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_id->setValidator ( new QIntValidator(0, 99999999, this));
    ui->tab_citoyen->setModel(C.afficher());
    ui->tab_citoyen_2->setModel(C.afficher());
    ui->tab_demande->setModel(d.afficher());
     ui->tab_demande_2->setModel(d.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


//void MainWindow::on_pushButton_clicked()
//{
//    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);

//}



void MainWindow::on_pushButton_Ajouter_clicked()

{
    int CIN=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->lineEdit_16->text();
    QString adresse=ui->le_adresse->text();
   QDate date=ui->dateEdit->date();

    Citoyen C(CIN,nom,prenom,adresse,date);
    bool test = C.ajouter();

    if (test){

 ui->tab_citoyen->setModel(C.afficher());
 ui->tab_citoyen_2->setModel(C.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}



void MainWindow::on_supp_button_clicked()
{
    int CIN  = ui->le_supp->text().toInt();
    bool test = c1.supprimer(CIN);

    if (test){

 ui->tab_citoyen->setModel(C.afficher());
 ui->tab_citoyen_2->setModel(C.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_update_button_clicked()
{

        int CIN=ui->le_cin->text().toInt();
        QString nom=ui->le_nom->text();
        QString prenom=ui->lineEdit_16->text();
        QString adresse=ui->le_adresse->text();
         QDate date=ui->dateEdit->date();

        Citoyen C(CIN,nom,prenom,adresse,date);
        bool test = C.modifier(CIN);

        if (test){

     ui->tab_citoyen->setModel(C.afficher());
     ui->tab_citoyen_2->setModel(C.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Modification effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);




}

void MainWindow::on_pushButton_Ajouter_2_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString type=ui->le_type->text();


     demandes_administratives d(id,nom,type);
    bool test = d.ajouter_2();

    if (test){

 ui->tab_demande->setModel(d.afficher());
 ui->tab_demande_2->setModel(d.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}



void MainWindow::on_pushButton_supp_2_clicked()

{

    int id  = ui->le_supp_2->text().toInt();
    bool test = d1.supprimer(id);

    if (test){

ui->tab_demande->setModel(d.afficher());
 ui->tab_demande_2->setModel(d.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_pushButton_modifier_2_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString type=ui->le_type->text();


    demandes_administratives d(id,nom,type);
    bool test = d.modifier(id);

    if (test){

 ui->tab_demande->setModel(d.afficher());
 ui->tab_demande_2->setModel(d.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);




}


