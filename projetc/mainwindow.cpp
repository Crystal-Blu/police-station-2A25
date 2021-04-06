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
#include <QPageLayout>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->tableViewpolice->setModel(police.afficher());
    ui->tableViewmissions->setModel(mission.afficher());
    ui->le_missionid->setReadOnly(true);
    ui->le_missionname->setReadOnly(true);
    ui->le_missiontype->setReadOnly(true);
    ui->de_missiondate->setReadOnly(true);
    ui->le_missionpoliceid->setReadOnly(true);
    ui->le_missionspolicename->setReadOnly(true);
    ui->le_missionspoliceprenom->setReadOnly(true);
    ui->le_nompoliceafficher->setReadOnly(true);
    ui->le_prenompoliceafficher->setReadOnly(true);
    ui->le_gradeafficher->setReadOnly(true);
    ui->le_policeidafficher->setReadOnly(true);
    ui->le_chefidafficher->setReadOnly(true);





    if(ui->le_missionidadd->text().isEmpty() or ui->le_missionnameadd->text().isEmpty() or ui->le_missiontypeadd->text().isEmpty()  or ui->le_missionpoliceidadd->text().isEmpty() or ui->de_missiondateadd->text().isEmpty() )
    {
        ui->pb_missionadd->setDisabled(1);

    }
    else
    {
        ui->pb_missionadd->setDisabled(0);
    }




    if(ui->le_policeid->text().isEmpty() or ui->le_grade->text().isEmpty() or ui->le_prenompolice->text().isEmpty()  or ui->le_nompolice->text().isEmpty() or ui->le_chefid->text().isEmpty() )
    {
        ui->pb_addpolice->setDisabled(1);

    }
    else
    {
        ui->pb_addpolice->setDisabled(0);
    }



    //ADD policier

    ui->le_policeid->setValidator ( new QIntValidator(0, 100, this));
    ui->le_grade->setMaxLength(20);
    ui->le_prenompolice->setMaxLength(20);
    ui->le_nompolice->setMaxLength(20);
    ui->le_chefid->setValidator ( new QIntValidator(0, 100, this));

    //Modifier policier

    ui->le_grademodifier->setMaxLength(20);
    ui->le_prenommodifier->setMaxLength(20);
    ui->le_nompolicemodifier->setMaxLength(20);
    ui->le_chefidmodifier->setValidator ( new QIntValidator(0, 100, this));

    //ADD mission
    ui->le_missionidadd->setValidator ( new QIntValidator(0, 100, this));
    ui->le_missionnameadd->setMaxLength(20);
    ui->le_missiontypeadd->setMaxLength(20);
    ui->le_missionpoliceidadd->setValidator ( new QIntValidator(0, 100, this));

    //Modifer mission
    ui->le_missionnamemodifier->setMaxLength(20);
    ui->le_missiontypemodifier->setMaxLength(20);
    ui->le_missionpoliceidmodifier->setValidator ( new QIntValidator(0, 100, this));


















}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_addpolice_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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

            ui->le_missionid->setReadOnly(true);
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base,Qt::white);
            palette->setColor(QPalette::Text,Qt::darkGray);
            ui->le_missionid->setPalette(*palette);

            ui->le_missionname->setText(qry.value(1).toString());

            ui->le_missionname->setReadOnly(true);
            QPalette *palette1 = new QPalette();
            palette1->setColor(QPalette::Base,Qt::white);
            palette1->setColor(QPalette::Text,Qt::darkGray);
            ui->le_missionname->setPalette(*palette);

            ui->le_missiontype->setText(qry.value(2).toString());

            ui->le_missiontype->setReadOnly(true);
            QPalette *palette2 = new QPalette();
            palette2->setColor(QPalette::Base,Qt::white);
            palette2->setColor(QPalette::Text,Qt::darkGray);
            ui->le_missiontype->setPalette(*palette);

            //ui->le_missionshowdate->setText(qry.value(3).toString());
            ui->de_missiondate->setDate(qry.value(3).toDate());

            ui->de_missiondate->setReadOnly(true);
            QPalette *palette3 = new QPalette();
            palette3->setColor(QPalette::Base,Qt::white);
            palette3->setColor(QPalette::Text,Qt::darkGray);
            ui->de_missiondate->setPalette(*palette);

            //ui->le_missionspolicename->setText(qry.value(4).toString());
            ui->le_missionpoliceid->setText(qry.value(4).toString());

            ui->le_missionpoliceid->setReadOnly(true);
            QPalette *palette4 = new QPalette();
            palette4->setColor(QPalette::Base,Qt::white);
            palette4->setColor(QPalette::Text,Qt::darkGray);
            ui->le_missionpoliceid->setPalette(*palette);

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

                    ui->le_missionspolicename->setReadOnly(true);


                    ui->le_missionspoliceprenom->setText(query.value(1).toString());

                    ui->le_missionspoliceprenom->setReadOnly(true);

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
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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
       QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
       music->play();

    // ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);
}

void MainWindow::on_pb_missionstaketoadd_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
     ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-2);
}

void MainWindow::on_pb_missionadd_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
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

         QSqlQuery qry;
         qry.prepare( " SELECT COUNT( * ) as numberofmissions FROM MISSIONS WHERE idp=:idp " );
         qry.bindValue(":idp", idp);
         qry.exec();
         qry.next();
         int nombredemisisons=qry.value(0).toInt();



         if(nombredemisisons<5)
         {
             QSqlQuery query;
             QString grade="workingman";
             query.prepare("update  POLICIER set   grade='"+grade+"'   where idp= :idp ");
             query.bindValue(":idp", idp);

             if(query.exec())
             {
                 //QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modifier effectué\n" "Click Cancel to exit"), QMessageBox::Cancel );
                  ui->tableViewpolice->setModel(police.afficher());
             }
             else
                    QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("modifier non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);



         }

         if(nombredemisisons>=5)
         {
             QSqlQuery query;
             QString grade="chef";
             query.prepare("update  POLICIER set   grade='"+grade+"'   where idp= :idp ");
             query.bindValue(":idp", idp);

             if(query.exec())
             {
                // QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modifier effectué\n" "Click Cancel to exit"), QMessageBox::Cancel );
                  ui->tableViewpolice->setModel(police.afficher());
             }
             else
                    QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("modifier non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);



         }







    }
    else
           QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);




    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-3);
}


void MainWindow::on_pb_missioninfoprint_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
    QPdfWriter pdf("C:/Users/xDrais/Desktop/Pdfdetention.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);

                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Detentions");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/xDrais/Desktop/dsfsdfsdf.png"));
                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.setPen(Qt::blue);
                                     painter.drawText(300,3300,"idm");
                                     painter.drawText(2300,3300,"nom");
                                     painter.drawText(4300,3300,"type");
                                     painter.drawText(6300,3300,"date_mission");
                                     painter.drawText(8500,3300,"idp");
                                     //painter.drawText(8000,3300,"ID_CEL");



                                     QSqlQuery query;
                                     query.prepare("select * from MISSIONS");
                                     query.exec();
                                     while (query.next())
                                     {
                                         painter.drawText(300,i,query.value(0).toString());
                                         painter.drawText(2300,i,query.value(1).toString());
                                         painter.drawText(4300,i,query.value(2).toString());
                                         painter.drawText(6300,i,query.value(3).toString());
                                         painter.drawText(8500,i,query.value(4).toString());
                                      //  painter.drawText(8000,i,query.value(5).toString());



                                        i = i +500;
                                     }
                                     int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                         QMessageBox::Yes |  QMessageBox::No);
                                         if (reponse == QMessageBox::Yes)
                                         {
                                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/xDrais/Desktop/Pdfdetention.pdf"));

                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();
    }
}







void MainWindow::on_pb_darkmode_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
    QFile f("C:/Users/xDrais/Desktop/qt/qtprojetc++/projetcCopy/dark/style.qss");

    if (!f.exists())   {
       qDebug("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
    }

}

void MainWindow::on_pb_lightmode_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
    QFile f("C:/Users/xDrais/Desktop/qt/qtprojetc++/projetcCopy/light/style.qss");

    if (!f.exists())   {
       qDebug("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
    }

}

void MainWindow::on_pb_darkorange_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
    QFile f("C:/Users/xDrais/Desktop/qt/qtprojetc++/projetcCopy/darkorange/darkorange.qss");

    if (!f.exists())   {
       qDebug("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_pb_defaultmode_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sound/click.wav"));
    music->play();
     setStyleSheet("");
}




void MainWindow::on_le_grade_textEdited(const QString &arg1)
{
    if(ui->le_policeid->text().isEmpty() or ui->le_grade->text().isEmpty() or ui->le_prenompolice->text().isEmpty()  or ui->le_nompolice->text().isEmpty() or ui->le_chefid->text().isEmpty() )
    {
        ui->pb_addpolice->setDisabled(1);

    }
    else
    {
        ui->pb_addpolice->setDisabled(0);
    }

}

void MainWindow::on_le_policeid_textEdited(const QString &arg1)
{
    if(ui->le_policeid->text().isEmpty() or ui->le_grade->text().isEmpty() or ui->le_prenompolice->text().isEmpty()  or ui->le_nompolice->text().isEmpty() or ui->le_chefid->text().isEmpty() )
    {
        ui->pb_addpolice->setDisabled(1);

    }
    else
    {
        ui->pb_addpolice->setDisabled(0);
    }

}

void MainWindow::on_le_prenompolice_textEdited(const QString &arg1)
{
    if(ui->le_policeid->text().isEmpty() or ui->le_grade->text().isEmpty() or ui->le_prenompolice->text().isEmpty()  or ui->le_nompolice->text().isEmpty() or ui->le_chefid->text().isEmpty() )
    {
        ui->pb_addpolice->setDisabled(1);

    }
    else
    {
        ui->pb_addpolice->setDisabled(0);
    }

}

void MainWindow::on_le_nompolice_textEdited(const QString &arg1)
{
    if(ui->le_policeid->text().isEmpty() or ui->le_grade->text().isEmpty() or ui->le_prenompolice->text().isEmpty()  or ui->le_nompolice->text().isEmpty() or ui->le_chefid->text().isEmpty() )
    {
        ui->pb_addpolice->setDisabled(1);

    }
    else
    {
        ui->pb_addpolice->setDisabled(0);
    }

}

void MainWindow::on_le_chefid_textEdited(const QString &arg1)
{
    if(ui->le_policeid->text().isEmpty() or ui->le_grade->text().isEmpty() or ui->le_prenompolice->text().isEmpty()  or ui->le_nompolice->text().isEmpty() or ui->le_chefid->text().isEmpty() )
    {
        ui->pb_addpolice->setDisabled(1);

    }
    else
    {
        ui->pb_addpolice->setDisabled(0);
    }

}

void MainWindow::on_le_grademodifier_textEdited(const QString &arg1)
{
    if(ui->le_grademodifier->text().isEmpty() or ui->le_prenommodifier->text().isEmpty() or ui->le_nompolicemodifier->text().isEmpty()  or ui->le_chefidmodifier->text().isEmpty() )
    {
        ui->pb_modifiepolice->setDisabled(1);

    }
    else
    {
        ui->pb_modifiepolice->setDisabled(0);
    }
}

void MainWindow::on_le_prenommodifier_textEdited(const QString &arg1)
{
    if(ui->le_grademodifier->text().isEmpty() or ui->le_prenommodifier->text().isEmpty() or ui->le_nompolicemodifier->text().isEmpty()  or ui->le_chefidmodifier->text().isEmpty() )
    {
        ui->pb_modifiepolice->setDisabled(1);

    }
    else
    {
        ui->pb_modifiepolice->setDisabled(0);
    }
}



void MainWindow::on_le_nompolicemodifier_textEdited(const QString &arg1)
{
    if(ui->le_grademodifier->text().isEmpty() or ui->le_prenommodifier->text().isEmpty() or ui->le_nompolicemodifier->text().isEmpty()  or ui->le_chefidmodifier->text().isEmpty() )
    {
        ui->pb_modifiepolice->setDisabled(1);

    }
    else
    {
        ui->pb_modifiepolice->setDisabled(0);
    }
}

void MainWindow::on_le_chefidmodifier_textEdited(const QString &arg1)
{
    if(ui->le_grademodifier->text().isEmpty() or ui->le_prenommodifier->text().isEmpty() or ui->le_nompolicemodifier->text().isEmpty()  or ui->le_chefidmodifier->text().isEmpty() )
    {
        ui->pb_modifiepolice->setDisabled(1);

    }
    else
    {
        ui->pb_modifiepolice->setDisabled(0);
    }
}

void MainWindow::on_le_missionidadd_textEdited(const QString &arg1)
{
    if(ui->le_missionidadd->text().isEmpty() or ui->le_missionnameadd->text().isEmpty() or ui->le_missiontypeadd->text().isEmpty()  or ui->le_missionpoliceidadd->text().isEmpty() or ui->de_missiondateadd->text().isEmpty() )
    {
        ui->pb_missionadd->setDisabled(1);

    }
    else
    {
        ui->pb_missionadd->setDisabled(0);
    }
}

void MainWindow::on_le_missionnameadd_textEdited(const QString &arg1)
{
    if(ui->le_missionidadd->text().isEmpty() or ui->le_missionnameadd->text().isEmpty() or ui->le_missiontypeadd->text().isEmpty()  or ui->le_missionpoliceidadd->text().isEmpty() or ui->de_missiondateadd->text().isEmpty() )
    {
        ui->pb_missionadd->setDisabled(1);

    }
    else
    {
        ui->pb_missionadd->setDisabled(0);
    }
}

void MainWindow::on_le_missiontypeadd_textEdited(const QString &arg1)
{
    if(ui->le_missionidadd->text().isEmpty() or ui->le_missionnameadd->text().isEmpty() or ui->le_missiontypeadd->text().isEmpty()  or ui->le_missionpoliceidadd->text().isEmpty() or ui->de_missiondateadd->text().isEmpty() )
    {
        ui->pb_missionadd->setDisabled(1);

    }
    else
    {
        ui->pb_missionadd->setDisabled(0);
    }
}

void MainWindow::on_le_missionpoliceidadd_textEdited(const QString &arg1)
{
    if(ui->le_missionidadd->text().isEmpty() or ui->le_missionnameadd->text().isEmpty() or ui->le_missiontypeadd->text().isEmpty()  or ui->le_missionpoliceidadd->text().isEmpty() or ui->de_missiondateadd->text().isEmpty() )
    {
        ui->pb_missionadd->setDisabled(1);

    }
    else
    {
        ui->pb_missionadd->setDisabled(0);
    }
}

void MainWindow::on_de_missiondateadd_dateChanged(const QDate &date)
{
    if(ui->le_missionidadd->text().isEmpty() or ui->le_missionnameadd->text().isEmpty() or ui->le_missiontypeadd->text().isEmpty()  or ui->le_missionpoliceidadd->text().isEmpty() or ui->de_missiondateadd->text().isEmpty() )
    {
        ui->pb_missionadd->setDisabled(1);

    }
    else
    {
        ui->pb_missionadd->setDisabled(0);
    }
}

void MainWindow::on_le_missionnamemodifier_textEdited(const QString &arg1)
{
    if(ui->le_missionnamemodifier->text().isEmpty() or ui->le_missiontypemodifier->text().isEmpty() or ui->le_missionpoliceidmodifier->text().isEmpty()  )
    {
        ui->pb_mission->setDisabled(1);

    }
    else
    {
        ui->pb_mission->setDisabled(0);
    }
}

void MainWindow::on_le_missiontypemodifier_textEdited(const QString &arg1)
{
    if(ui->le_missionnamemodifier->text().isEmpty() or ui->le_missiontypemodifier->text().isEmpty() or ui->le_missionpoliceidmodifier->text().isEmpty()  )
    {
        ui->pb_mission->setDisabled(1);

    }
    else
    {
        ui->pb_mission->setDisabled(0);
    }
}

void MainWindow::on_le_missionpoliceidmodifier_textEdited(const QString &arg1)
{
    if(ui->le_missionnamemodifier->text().isEmpty() or ui->le_missiontypemodifier->text().isEmpty() or ui->le_missionpoliceidmodifier->text().isEmpty()  )
    {
        ui->pb_mission->setDisabled(1);

    }
    else
    {
        ui->pb_mission->setDisabled(0);
    }
}

void MainWindow::on_de_missiondatemodifier_userDateChanged(const QDate &date)
{
    if(ui->le_missionnamemodifier->text().isEmpty() or ui->le_missiontypemodifier->text().isEmpty() or ui->le_missionpoliceidmodifier->text().isEmpty()  )
    {
        ui->pb_mission->setDisabled(1);

    }
    else
    {
        ui->pb_mission->setDisabled(0);
    }
}
