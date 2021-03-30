#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "policier.h"
#include "missions.h"
#include <QSqlQuery>
#include <QDebug>
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
    ui->tableViewpolice->setModel(police.afficher());
    ui->tableViewmissions->setModel(mission.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
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
    qry.prepare( " select * from POLICIER where idp ='"+val+"'   "   );
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
    query.prepare("update  POLICIER set  nom= '"+nom+"', prenom='"+prenom+"', grade='"+grade+"'  , idpchef= '"+resss+"' where idp= :idp ");
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



void MainWindow::on_tableViewmissions_activated(const QModelIndex &index)
{
    QString val=ui->tableViewmissions->model()->data(index).toString();
    QSqlQuery qry;

    qry.prepare( " select * from MISSIONS where  idm='"+val+"'  "   );

    if(qry.exec( ) )
    {
        while( qry.next()  )
    {
            ui->le_missionid->setText(qry.value(0).toString());
            ui->le_missionname->setText(qry.value(1).toString());
            ui->le_missiontype->setText(qry.value(2).toString());
            //ui->le_missionshowdate->setText(qry.value(3).toString());
            ui->de_missiondate->setDate(qry.value(3).toDate());

            //ui->le_missionspolicename->setText(qry.value(4).toString());
            ui->le_missionpoliceid->setText(qry.value(4).toString());

            int idp = ui->le_missionpoliceid->text().toInt();
            QSqlQuery query;
            QString res=QString::number(idp);
            query.prepare("select nom,prenom from POLICIER where idp= :idp ");
            query.bindValue(":idp",res);
            if(query.exec( ))
            {
                while(query.next())

            {
                    ui->le_missionspolicename->setText(query.value(0).toString());
                    ui->le_missionspoliceprenom->setText(query.value(1).toString());



            }

            }

    }

    }
    else
    {
      QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("selection non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

    }



}

void MainWindow::on_pb_missionsdelete_clicked()
{
    int idm =ui->le_missionid->text().toInt();
    bool test=mission.supprimer(idm);
    if(test)
         {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("supprimer successful.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableViewmissions->setModel(mission.afficher());
        ui->le_missionid->clear();
        ui->le_missionname->clear();
        ui->le_missiontype->clear();
        ui->de_missiondate->clear();
        ui->le_missionpoliceid->clear();
        ui->le_missionspolicename->clear();
        ui->le_missionspoliceprenom->clear();

    }
    else
       {

        QMessageBox::information(nullptr, QObject::tr("NOT OK"), QObject::tr("supprimer NOT successful.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_missionsmodifier_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-1);

    int idm=ui->le_missionid->text().toInt();
    QString res=QString::number(idm);
    QSqlQuery qry;
    qry.prepare( " select * from MISSIONS where idm= '"+res+"'  " );
    if(qry.exec( ))
    {
        while(qry.next())

    {
            ui->le_missionidmodifier->setText(qry.value(0).toString());
            ui->le_missionidmodifier->setReadOnly(true);
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base,Qt::gray);
            palette->setColor(QPalette::Text,Qt::darkGray);
            ui->le_missionidmodifier->setPalette(*palette);

            ui->le_missionnamemodifier->setText(qry.value(1).toString());
            ui->le_missiontypemodifier->setText(qry.value(2).toString());
            ui->le_missionpoliceidmodifier->setText(qry.value(4).toString());
            ui->le_missionnamemodifier->setText(qry.value(1).toString());
            ui->de_missiondatemodifier->setDate(qry.value(3).toDate());



    }

    }
    else
    {
      QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("selection non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

    }
}



void MainWindow::on_pb_mission_clicked()
{

    int idm = ui->le_missionidmodifier->text().toInt();

    QString nom=ui->le_missionnamemodifier->text();
    QString type=ui->le_missiontypemodifier->text();
    QDate date_mission=ui->de_missiondatemodifier->date();
    int idp = ui->le_missionpoliceidmodifier->text().toInt();
    QString res=QString::number(idm);
    QString resss=QString::number(idp);
    QSqlQuery query;
    query.prepare("update  MISSIONS set  nom= '"+nom+"', type='"+type+"', date_mission= :date_mission , idp= '"+resss+"' where idm= :idm ");
    query.bindValue(":idm", res);
    query.bindValue(":idp", resss);
    query.bindValue(":date_mission", date_mission);


    if(query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modifier effectué\n" "Click Cancel to exit"), QMessageBox::Cancel );
         ui->tableViewmissions->setModel(mission.afficher());

         ui->le_missionidmodifier->clear();
         ui->le_missionnamemodifier->clear();
         ui->le_missiontypemodifier->clear();
         ui->le_missionpoliceidmodifier->clear();
         ui->le_missionid->clear();
         ui->le_missionname->clear();
         ui->le_missiontype->clear();
         ui->le_missionpoliceid->clear();
         ui->le_missionspolicename->clear();
         ui->le_missionspoliceprenom->clear();






         ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-3);
    }

    else
           QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("modifier non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);



}


void MainWindow::on_le_searchplice_textChanged(const QString &arg1)
{
    if(ui->rb_searchpoliceparnom->isChecked())
    {
        QSqlQuery query;
        QSqlQueryModel * model=new QSqlQueryModel();
        query.prepare("SELECT * FROM POLICIER WHERE nom LIKE :surname");
        query.bindValue(":surname", QString("%%1%").arg(arg1));
        query.exec();
        model->setQuery(query);
        ui->tableViewpolice->setModel(model);
        qDebug() <<(model->rowCount());
    }

    if(ui->rb_searchpoliceparprenom->isChecked())
    {
        QSqlQuery query;
        QSqlQueryModel * model=new QSqlQueryModel();
        query.prepare("SELECT * FROM POLICIER WHERE prenom LIKE :surname");
        query.bindValue(":surname", QString("%%1%").arg(arg1));
        query.exec();
        model->setQuery(query);
        ui->tableViewpolice->setModel(model);
        qDebug() <<(model->rowCount());
    }

    if(ui->rb_searchpoliceparid->isChecked())
    {
        QSqlQuery query;
        QSqlQueryModel * model=new QSqlQueryModel();
        query.prepare("SELECT * FROM POLICIER WHERE idp LIKE :surname");
        query.bindValue(":surname", QString("%%1%").arg(arg1));
        query.exec();
        model->setQuery(query);
        ui->tableViewpolice->setModel(model);
        qDebug() <<(model->rowCount());
    }
}

void MainWindow::on_pb_policetaketomodifier_clicked()
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

void MainWindow::on_pb_policesupprimer_clicked()
{
    int idp =ui->le_policeidafficher->text().toInt();
    bool test=police.supprimer(idp);
    if(test)
         {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("supprimer successful.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableViewpolice->setModel(police.afficher());
        ui->tableViewmissions->setModel(mission.afficher());

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

void MainWindow::on_pb_policetaketoadd_clicked()
{
     ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);
}

void MainWindow::on_pb_missionstaketoadd_clicked()
{
     ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-2);
}

void MainWindow::on_pb_missionadd_clicked()
{
    int idm = ui->le_missionidadd->text().toInt();
    QString nom=ui->le_missionnameadd->text();
    QString type=ui->le_missiontypeadd->text();
    QDate date_mission = ui->de_missiondateadd->date();
    int idp = ui->le_missionpoliceidadd->text().toInt();

    missions m(idm , nom , type , date_mission,idp);
    bool test=m.ajouter();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\n" "Click Cancel to exit"), QMessageBox::Cancel );
         ui->tableViewmissions->setModel(mission.afficher());
         ui->le_missionidadd->clear();
         ui->le_missionnameadd->clear();
         ui->le_missiontypeadd->clear();

    }
    else
           QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);




    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-3);
}


void MainWindow::on_pb_missioninfoprint_clicked()
{
   /*
    QPrinter printer;
    printer.setPrinterName("deired printer name");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()== QDialog::Rejected ) return;
*/
   /*
    int width = 0;
    int height = 0;

  ui->tableViewmissions->resizeColumnsToContents();
    ui->tableViewmissions->resizeRowsToContents();

    const int columnCnt = ui->tableViewmissions->model()->columnCount();
    for( int i = 0; i < columnCnt; ++i )
    {
        width += ui->tableViewmissions->columnWidth(i) ;
    }
   width=width*2;

    const int rowCnt = ui->tableViewmissions->model()->rowCount();
    for( int i = 0; i < rowCnt; ++i )
    {

        height += ui->tableViewmissions->rowHeight(i)  ;

    }
    height=height*2;

    ui->tableViewmissions->setFixedSize(width, height);

    QPrinter printer;

    // ... printer settings ...

    ui->tableViewmissions->render(&printer);
     */
}












