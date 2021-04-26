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
#include <QTextStream>
#include <QDebug>
#include "arduino.h"
#include <QFile>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->idc->setValidator ( new QIntValidator(0, 10, this));
    ui->idc_md->setValidator ( new QIntValidator(0, 10, this));
    ui->idc_supp->setValidator ( new QIntValidator(0, 10, this));
    ui->nblit->setValidator ( new QIntValidator(0, 10, this));
    ui->nb_lit_md->setValidator ( new QIntValidator(0, 10, this));
    ui->id_det->setValidator ( new QIntValidator(0, 10000, this));
    ui->id_det_md->setValidator ( new QIntValidator(0, 10000, this));
    ui->id_det_supp->setValidator ( new QIntValidator(0, 10000, this));
    ui->raison_det->setMaxLength(20);
    ui->raison_maya_md->setMaxLength(20);
    ui->raison_det->setPlaceholderText("saisir la raison de la detention");
    ui->raison_maya_md->setMaxLength(20);
    ui->raison_maya_md->setPlaceholderText("saisir la raison de la detention");
    ui->tableView_cellule->setModel(C.afficher());
    ui->tableView_detention->setModel(D.afficher());


    //arduino
    int ret=A.connect_arduino();
    switch (ret) {
    case(0): qDebug() << "arduino is available and connected to :" <<A.getarduino_port_name();
    break ;
    case(1): qDebug() << "arduino is available and not connected to :" <<A.getarduino_port_name();
    break ;
    case(-1): qDebug() << "arduino is not available";
        break;

        }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label_lumiere()));





}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ajouter_cel_clicked()
{
    int idcel=ui->idc->text().toInt();
    int nombre_det=ui->nbdet->text().toInt();
    int nombre_det_max=ui->nbdetmax->text().toInt();
    int nombre_lit=ui->nblit->text().toInt();



        Cellules C(idcel,nombre_det,nombre_det_max,nombre_lit);
        bool test = C.ajouter();

        if (test){

     ui->tableView_cellule->setModel(C.afficher());
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


void MainWindow::on_pushButton_modifier_cel_clicked()
{

    int idcel=ui->idc_md->text().toInt();
    int nombre_det=ui->nb_det_md->text().toInt();
    int nombre_det_max=ui->nb_det_max_md->text().toInt();
    int nombre_lit=ui->nb_lit_md->text().toInt();


    Cellules C(idcel,nombre_det,nombre_det_max,nombre_lit);
    bool test = C.modifier(idcel);

    if (test){

 ui->tableView_cellule->setModel(C.afficher());
 ui->idc_md->clear();
 ui->nb_det_md->clear();
 ui->nb_det_max_md->clear();
 ui->nb_lit_md->clear();


        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification de la cellule effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

}



void MainWindow::on_pushButton_supp_cel_clicked()
{
    int idcel  = ui->idc_supp->text().toInt();
        bool test = C1.supprimer(idcel);

        if (test){

     ui->tableView_cellule->setModel(C.afficher());
     ui->idc_supp->clear();

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}





void MainWindow::on_pushButton_ajouter_det_clicked()
{
    int iddet=ui->id_det->text().toInt();
    QDate date_entree=ui->date_entree->date();
    QDate date_sortie=ui->date_sortie->date();
    QString raison=ui->raison_det->text();
    int idcel=ui->idcel_2->text().toInt();
    int idp=ui->idp_maya->text().toInt();



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
     ui->tableView_detention->setModel(D.afficher());
     ui->tableView_cellule->setModel(C.afficher());
     ui->id_det->clear();
     ui->date_entree->clear();
     ui->date_sortie->clear();
     ui->raison_det->clear();
     ui->idcel_2->clear();
     ui->idp_maya->clear();


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
void MainWindow::on_pushButton_modifier_det_clicked()
{
    int iddet=ui->id_det_md->text().toInt();
    QDate date_entree=ui->date_entree_md->date();
    QDate date_sortie=ui->date_sortie_md->date();
    QString raison=ui->raison_maya_md->text();
    int idcel=ui->id_cel_2_md->text().toInt();
    int idp=ui->idp_maya_2_md->text().toInt();

           detentions D(iddet,date_entree,date_sortie,raison,idcel,idp);
           bool test = D.modifier(iddet);

           if (test){

        ui->tableView_detention->setModel(D.afficher());
        ui->id_det_md->clear();
        ui->date_entree_md->clear();
        ui->date_sortie_md->clear();
        ui->raison_maya_md->clear();
        ui->idp_maya_2_md->clear();
        ui->id_cel_2_md->clear();


               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("Modification de la detention effectuée avec succés\n"
       "Click Cancel to exit"),QMessageBox::Cancel);


           }
           else
               QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification de la detention non effectuée.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_pushButton_supprimer_det_clicked()
{
    int iddet  = ui->id_det_supp->text().toInt();
        bool test = D1.supprimer(iddet);

        if (test){

     ui->tableView_detention->setModel(D.afficher());
     ui->id_det_supp->clear();


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression de la detention effectuée avec succès\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression de la detention non effectuée.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_metier_pdf_clicked()
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
                                         QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/user/Desktop/Pdfdetention.pdf"));

                                         painter.end();
                                     }
                                     else
                                     {
                                          painter.end();
}
}

void MainWindow::on_le_recherche_maya_textChanged(const QString &arg1)
{
    if(ui->rb_idp_maya->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM DETENTIONS WHERE idp LIKE :rech");
            query.bindValue(":rech", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tableView_detention->setModel(model);

        }

    if(ui->rb_idcel->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM DETENTIONS WHERE idcel LIKE :rech");
            query.bindValue(":rech", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tableView_detention->setModel(model);

        }
    if(ui->rb_raison_maya->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM DETENTIONS WHERE raison LIKE :rech");
            query.bindValue(":rech", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tableView_detention->setModel(model);

        }
}

void MainWindow::on_pushButton_maya_1_clicked()
{
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-3);

}

void MainWindow::on_pushButton_maya_2_clicked()
{
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-2);
}



void MainWindow::on_pushButton_maya_3_clicked()
{
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-1);
}



void MainWindow::on_pushButton_maya_4_clicked()
{
    ui->tabWidget_4->setCurrentIndex(ui->tabcellule->count()-3);
}



void MainWindow::on_pushButton_maya_5_clicked()
{
    ui->tabWidget_4->setCurrentIndex(ui->tabcellule->count()-2);
}



void MainWindow::on_pushButton_maya_6_clicked()
{
    ui->tabWidget_4->setCurrentIndex(ui->tabcellule->count()-1);
}



void MainWindow::on_pushButton_md_sombre_clicked()
{
    QFile f("C:/Users/user/Desktop/khedma_projetC/police-station-2A25/dark/style.qss");

       if (!f.exists())   {
           printf("Unable to set stylesheet, file not found\n");
       }
       else   {
           f.open(QFile::ReadOnly | QFile::Text);
           QTextStream ts(&f);
           setStyleSheet(ts.readAll());
       }
}





void MainWindow::on_pushButton_md_clair_clicked()
{
    QFile f("C:/Users/user/Desktop/khedma_projetC/police-station-2A25/light/style.qss");

        if (!f.exists())   {
            printf("Unable to set stylesheet, file not found\n");
        }
        else   {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            setStyleSheet(ts.readAll());
        }
}


void MainWindow::on_pushButton_md_sombre_orange_clicked()
{
    QFile f("C:/Users/user/Desktop/khedma_projetC/police-station-2A25/DarkOrange/darkorange/darkorange.qss");

       if (!f.exists())   {
           printf("Unable to set stylesheet, file not found\n");
       }
       else   {
           f.open(QFile::ReadOnly | QFile::Text);
           QTextStream ts(&f);
           setStyleSheet(ts.readAll());
       }
}

void MainWindow::on_pushButton_md_original_clicked()
{
    setStyleSheet("");
}

void MainWindow::on_pushButton_lumiere_act_clicked() //activer systeme lumière
{
 A.write_to_arduino("1");
}



void MainWindow::on_pushButton_lumiere_desact_clicked() //desactiver systeme lumière
{
    A.write_to_arduino("0");
}

void MainWindow::update_label_lumiere()
{
    data=A.read_from_arduino();
    if (data=="1")
        ui->label_etat_lumiere->setText("lumières allumées");
    else if (data=="0" || data=="2")
        ui->label_etat_lumiere->setText("lumières eteinte");
}


