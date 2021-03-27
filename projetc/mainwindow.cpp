#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "policier.h"
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableViewpolice->setModel(police.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);

}

void MainWindow::on_pushButton_3_clicked()
{
    int idp =ui->le_policeidafficher->text().toInt();
    bool test=police.supprimer(idp);
    if(test)
         {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("supprimer successful.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableViewpolice->setModel(police.afficher());
        ui->le_chefidafficher->clear();
        ui->le_gradeafficher->clear();
        ui->le_nompoliceafficher->clear();
        ui->le_policeidafficher->clear();
        ui->le_prenompoliceafficher->clear();

    }
    else
       {

        QMessageBox::information(nullptr, QObject::tr("NOT OK"), QObject::tr("supprimer NOT successful.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    int idp=ui->le_policeidafficher->text().toInt();
    QString res=QString::number(idp);
    QSqlQuery qry;
    qry.prepare( " select * from POLICIER where idp= '"+res+"'  " );
    if(qry.exec( ))
    {
        while(qry.next())

    {
            ui->le_policeidmodifier->setText(qry.value(0).toString());
            ui->le_policeidmodifier->setReadOnly(true);
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base,Qt::gray);
            palette->setColor(QPalette::Text,Qt::darkGray);
            ui->le_policeidmodifier->setPalette(*palette);

            ui->le_nompolicemodifier->setText(qry.value(1).toString());
            ui->le_prenommodifier->setText(qry.value(2).toString());
            ui->le_chefidmodifier->setText(qry.value(4).toString());
            ui->le_grademodifier->setText(qry.value(3).toString());
            ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-1);


    }

    }
    else
    {
      QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("selection non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

    }




}

void MainWindow::on_pushButton_8_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-1);
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-1);

}

void MainWindow::on_pushButton_17_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-1);

}

void MainWindow::on_pushButton_18_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-1);

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-2);

}

void MainWindow::on_pushButton_19_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-3);

}

void MainWindow::on_pushButton_20_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-3);

}

void MainWindow::on_pb_addpolice_clicked()
{
    int idp = ui->le_policeid->text().toInt();
    QString nom=ui->le_nompolice->text();
    QString prenom=ui->le_prenompolice->text();
    QString grade=ui->le_grade->text();
    int idpchef = ui->le_chefid->text().toInt();

    policier p(idp,nom,prenom,grade,idpchef);
    bool test=p.ajouter();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\n" "Click Cancel to exit"), QMessageBox::Cancel );
         ui->tableViewpolice->setModel(police.afficher());
         ui->le_policeid->clear();
         ui->le_prenompolice->clear();
         ui->le_nompolice->clear();
         ui->le_grade->clear();
         ui->le_chefid->clear();
    }
    else
           QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);




    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-3);
}

void MainWindow::on_tableViewpolice_activated(const QModelIndex &index)
{
    QString val=ui->tableViewpolice->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare( " select * from POLICIER where grade ='"+val+"' or nom='"+val+"' or prenom='"+val+"'  "   );
    if(qry.exec( ))
    {
        while(qry.next())

    {
            ui->le_policeidafficher->setText(qry.value(0).toString());
            ui->le_nompoliceafficher->setText(qry.value(1).toString());
            ui->le_prenompoliceafficher->setText(qry.value(2).toString());
            ui->le_chefidafficher->setText(qry.value(4).toString());
            ui->le_gradeafficher->setText(qry.value(3).toString());




    }

    }
    else
    {
      QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("selection non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

    }


}

void MainWindow::on_pb_modifiepolice_clicked()
{
    int idp = ui->le_policeidmodifier->text().toInt();
    QString nom=ui->le_nompolicemodifier->text();
    QString prenom=ui->le_prenommodifier->text();
    QString grade=ui->le_grademodifier->text();
    int idpchef = ui->le_chefidmodifier->text().toInt();

    QString res=QString::number(idp);
    QString resss=QString::number(idpchef);
    QSqlQuery query;
    query.prepare("update  POLICIER set idp='"+res+"' , nom= '"+nom+"', prenom='"+prenom+"', grade='"+grade+"'  , idpchef= '"+resss+"' where idp= :idp ");
    query.bindValue(":idp", res);
    query.bindValue(":idpchef", resss);


    if(query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modifier effectué\n" "Click Cancel to exit"), QMessageBox::Cancel );
         ui->tableViewpolice->setModel(police.afficher());

         ui->le_chefidmodifier->clear();
         ui->le_nompolicemodifier->clear();
         ui->le_policeidmodifier->clear();
         ui->le_grademodifier->clear();
         ui->le_prenommodifier->clear();
    }
    else
           QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("modifier non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);



    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-3);

}


