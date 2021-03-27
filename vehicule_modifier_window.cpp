#include "vehicule_modifier_window.h"
#include "ui_vehicule_modifier_window.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlQueryModel>

vehicule_modifier_window::vehicule_modifier_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vehicule_modifier_window)
{

    ui->setupUi(this);
    /*ui->Marque->text()=vehicule_M.getmarque();
    ui->Matricule->text()=vehicule_M.getmarque();
    ui->Idp->text()=vehicule_M.getmarque();
    ui->dateEdit->date()=vehicule_M.getdate();*/
    qDebug ()<<vehicule_M.getmarque();

}

vehicule_modifier_window::~vehicule_modifier_window()
{
    delete ui;
}
void vehicule_modifier_window::remplir(QString matricule,QString idp, QDate date_ach,QString nom_marque)
{
    this->ui->Marque->setText(nom_marque);
     this->ui->Matricule->setText(matricule);
     this->ui->Idp->setText(idp);
     this->ui->dateEdit->setDate(date_ach);
}

void vehicule_modifier_window::on_pushButton_clicked()
{
    this->vehicule_M.Setnom_marque(this->ui->Marque->text());
    this->vehicule_M.SetMatricule( this->ui->Matricule->text().toInt());
     this->vehicule_M.SetidP(this->ui->Idp->text().toInt());
     this->vehicule_M.SetDate(this->ui->dateEdit->date());
    bool test=this->vehicule_M.modifier_vehicule();
    if (test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification Effectué avec succées \n"), QMessageBox::Ok);
    }
    if (!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),QObject::tr("Erreur \n"), QMessageBox::Ok);
    }
    this->close();


}
