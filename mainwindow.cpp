#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "cellule.h"
#include<QIntValidator>
#include "detention.h"
#include <QPrinter>
#include <QPrintDialog>
#include<QTextDocument>
#include<QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QPdfWriter>
#include <QSqlQuery>



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
     ui->idc->clear();
     ui->nbdet->clear();
     ui->nbdetmax->clear();
     ui->nblit->clear();


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
 ui->lineEdit->clear();
 ui->lineEdit_2->clear();
 ui->lineEdit_3->clear();
 ui->lineEdit_4->clear();


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
     ui->lineEdit_13->clear();

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
    int idcel=ui->lineEdit_10->text().toInt();
    int idp=ui->lineEdit_9->text().toInt();



        detentions D(iddet,date_entree,date_sortie,raison,idcel,idp);

            QSqlQuery query;

            QString idcel_string =   QString::number(idcel);
           query.prepare("select nombre_det,nombre_det_max from cellules where idcel = :idcel");

           query.bindValue(":idcel", idcel_string);
          if  (query.exec()) {
while (query.next()) {
    ui->nbdetmax->setText(query.value(0).toString());
    ui->nbdet->setText(query.value(1).toString());
}
}

           int nombre_det=ui->nbdet->text().toInt();
           int nombre_max=ui->nbdetmax->text().toInt();


        //bool test1=C.test_cmax(idcel);
              if(nombre_max!=nombre_det){


        bool test = D.ajouter();

        if (test){

     C.ajout_det(idcel);
     ui->tableView_2->setModel(D.afficher());
     ui->tableView->setModel(C.afficher());
     ui->lineEdit_5->clear();
     ui->dateEdit->clear();
     ui->dateEdit_2->clear();
     ui->lineEdit_8->clear();
     ui->lineEdit_10->clear();
     ui->lineEdit_9->clear();


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout de la detention effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}
               else
                   QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Nombre max atteint.Veuillez ajouter dans une autre cellule.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}
void MainWindow::on_pushButton_modifier2_clicked()
{
    int iddet=ui->lineEdit_11->text().toInt();
    QDate date_entree=ui->dateEdit_3->date();
    QDate date_sortie=ui->dateEdit_4->date();
    QString raison=ui->lineEdit_15->text();
    int idcel=ui->lineEdit_18->text().toInt();
    int idp=ui->lineEdit_17->text().toInt();

           detentions D(iddet,date_entree,date_sortie,raison,idcel,idp);
           bool test = D.modifier(iddet);

           if (test){

        ui->tableView_2->setModel(D.afficher());
        ui->lineEdit_11->clear();
        ui->dateEdit_3->clear();
        ui->dateEdit_4->clear();
        ui->lineEdit_15->clear();
        ui->lineEdit_17->clear();
        ui->lineEdit_18->clear();


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
     ui->lineEdit_12->clear();


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression de la detention effectuée avec succès\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression de la detention non effectuée.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_clicked()
{

    QPdfWriter pdf("C:/Users/user/desktop/Pdfdetention.pdf");
                             QPainter painter(&pdf);
                            int i = 4000;
                                 painter.setPen(Qt::red);

                                 painter.setFont(QFont("Arial", 30));
                                 painter.drawText(2100,1200,"Liste Des Detentions");
                                 painter.setPen(Qt::black);
                                 painter.setFont(QFont("Arial", 50));
                                 painter.drawRect(1000,200,6500,2000);
                                 painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/user/Desktop/khedma_projetC/police-station-2A25/detention.jpg"));
                                 painter.drawRect(0,3000,9600,500);
                                 painter.setFont(QFont("Arial", 9));
                                 painter.setPen(Qt::blue);
                                 painter.drawText(300,3300,"ID_DET");
                                 painter.drawText(2300,3300,"DATE_ENTREE");
                                 painter.drawText(4300,3300,"DATE_SORTIE");
                                 painter.drawText(6300,3300,"RAISON");
                                 painter.drawText(7500,3300,"ID_P");
                                 painter.drawText(8000,3300,"ID_CEL");



                                 QSqlQuery query;
                                 query.prepare("select * from DETENTIONS");
                                 query.exec();
                                 while (query.next())
                                 {
                                     painter.drawText(300,i,query.value(0).toString());
                                     painter.drawText(2300,i,query.value(1).toString());
                                     painter.drawText(4300,i,query.value(2).toString());
                                     painter.drawText(6300,i,query.value(3).toString());
                                     painter.drawText(7500,i,query.value(4).toString());
                                     painter.drawText(8000,i,query.value(5).toString());



                                    i = i +500;
                                 }
                                 int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                     QMessageBox::Yes |  QMessageBox::No);
                                     if (reponse == QMessageBox::Yes)
                                     {
                                         QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/user/desktop/Pdfdetention.pdf"));

                                         painter.end();
                                     }
                                     else
                                     {
                                          painter.end();
}
}

void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{
    if(ui->rb_idp->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM DETENTIONS WHERE idp LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tableView_2->setModel(model);

        }

    if(ui->rb_idcel->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM DETENTIONS WHERE idcel LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tableView_2->setModel(model);

        }
    if(ui->rb_raison->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM DETENTIONS WHERE raison LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tableView_2->setModel(model);

        }
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-3);

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-2);
}



void MainWindow::on_pushButton_4_clicked()
{
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-1);
}



void MainWindow::on_pushButton_13_clicked()
{
    ui->tabWidget_4->setCurrentIndex(ui->tabcellule->count()-3);
}



void MainWindow::on_pushButton_10_clicked()
{
    ui->tabWidget_4->setCurrentIndex(ui->tabcellule->count()-2);
}



void MainWindow::on_pushButton_8_clicked()
{
    ui->tabWidget_4->setCurrentIndex(ui->tabcellule->count()-1);
}
