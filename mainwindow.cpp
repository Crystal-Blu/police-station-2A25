#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "vehicule_modifier_window.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Vehicule_table->setModel(V.afficher_vehicules());

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);

}

void MainWindow::on_ajouter_clicked()
{
    bool test;
    int matricule=ui->MatriculeEdit->text().toInt();
    QString modele=ui->modeleEdit->text();
    int idp=ui->idpedit->text().toInt();
    QDate date_a=ui->dateEdit->date();
    vehicule Veh(matricule,modele,date_a,idp);
    test=Veh.ajouter_vehicule();
    if (test)
    {
         ui->tableView->setModel(V.afficher_vehicules());
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout Effectué avec succées \n"), QMessageBox::Ok);
    }
    if (!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),QObject::tr("Ajout Non Effectué \n"), QMessageBox::Ok);
    }

}

void MainWindow::on_Refresh_clicked()
{
    ui->Vehicule_table->setModel(V.afficher_vehicules());
}

int MainWindow::on_Vehicule_table_activated(const QModelIndex &index)
{
    QString val=ui->Vehicule_table->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare( " select * from vehicules where matricule ='"+val+"'  "   );
        if(qry.exec( ))
        {
            while(qry.next())

        {
                int matricule=qry.value(1).toInt();
                ui->matslected->setText(qry.value(1).toString());
                ui->Delete_button->setEnabled(true);
                ui->Modif_btton->setEnabled(true);
                ui->Demande_rep->setEnabled(true);
                ui->Assign_Police->setEnabled(true);

                return matricule;
        }

        }
        else
        {
          QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("clickez sur la matricule.\n" "Clic ok to exit."),QMessageBox::Ok);

        }
}



void MainWindow::on_Delete_button_clicked()
{
    int matricule=ui->matslected->text().toInt();
    V.delete_vehicule(matricule);
     ui->Vehicule_table->setModel(V.afficher_vehicules());
}

void MainWindow::on_Modif_btton_clicked()
{
    QSqlQuery qry;
    int matricule=ui->matslected->text().toInt();

    qry.prepare( " select * from vehicules where matricule ='"+ui->matslected->text()+"'  "   );
    if(qry.exec( ))
    {
        while(qry.next())

    {
            WM.vehicule_M.SetMatricule(qry.value(1).toInt());
            WM.vehicule_M.Setnom_marque(qry.value(0).toString());
            WM.vehicule_M.SetidP(qry.value(3).toInt());
            WM.vehicule_M.SetDate(qry.value(2).toDate());
            //qDebug ()<<WM.vehicule_M.getmarque();
            //qDebug ()<<qry.value(0).toString();
    }
    }
    int mat=WM.vehicule_M.getmatricule();
    QString s = QString::number(mat);
    QString i = QString::number(WM.vehicule_M.getidp());
    WM.remplir(s,i,WM.vehicule_M.getdate(),WM.vehicule_M.getmarque());
    WM.show();
}






void MainWindow::on_pushButton_21_clicked()
{
    if(V.verify_matricule(ui->MatriculeEdit->text().toInt()))
    {
        ui->label_13->setText("Matricule Existante");
        ui->label_13->setStyleSheet("QLabel {color : red; }");
    }
    else
    {
        ui->label_13->setText("Matricule Disponible");
        ui->label_13->setStyleSheet("QLabel {color : green; }");
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    if(V.verify_Police_id(ui->idpedit->text().toInt()))
    {
        ui->label_14->setText("Police Id Existant");
        ui->label_14->setStyleSheet("QLabel {color : green; }");

    }
    else
    {
        ui->label_14->setText("Police Id non Existant");
        ui->label_14->setStyleSheet("QLabel {color : red; }");
    }
}
