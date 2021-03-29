#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citoyen.h"
#include "connection.h"
#include<QMessageBox>
#include<QPdfWriter>
#include<QSqlQuery>
#include<QSqlError>
#include<QIntValidator>
#include <QDateEdit>
#include<QDateTimeEdit>
#include <QSqlDatabase>
#include<QFileDialog>
#include<QFile>
#include<QImage>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator ( new QIntValidator(0, 99999999, this));
      ui->le_cin->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_supp->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_supp_2->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_id->setValidator ( new QIntValidator(0, 99999999, this));
    ui->tab_citoyen->setModel(C.afficher());
    ui->tab_citoyen_2->setModel(C.afficher());
    ui->tab_demande->setModel(d.afficher());
     ui->tab_demande_2->setModel(d.afficher());
      ui->tableView->setModel(d.afficher());


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
  //QByteArray photo  = ui->label_21-> ;

   QDate DATE_NAISSANCE=ui->dateEdit->date() ;

    Citoyen C(CIN,nom,prenom,adresse/*,photo*/,DATE_NAISSANCE);
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
     //QByteArray photo =ui->label_21->setPixmap;
         QDate DATE_NAISSANCE=ui->dateEdit->date();







        Citoyen C(CIN,nom,prenom,adresse/*,photo*/,DATE_NAISSANCE);
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
    QDateTime DATE_CREATION=ui->dateTimeEdit_D_1->dateTime().currentDateTime();

     demandes_administratives d(id,nom,type,DATE_CREATION);
    bool test = d.ajouter_2();

    if (test){

 ui->tab_demande->setModel(d.afficher());
 ui->tab_demande_2->setModel(d.afficher());
 ui->tableView->setModel(d.afficher());

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

    if (test ){

ui->tab_demande->setModel(d.afficher());
 ui->tab_demande_2->setModel(d.afficher());
 ui->tableView->setModel(d.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_pushButton_modifier_2_clicked()
{
    int id=ui->le_id_2->text().toInt();
    QString nom=ui->le_id_3->text();
    QString type=ui->le_id_4->text();
    QDateTime DATE_CREATION=ui->dateTimeEdit-> dateTime().currentDateTime();


    demandes_administratives d(id,nom,type,DATE_CREATION);
    bool test = d.modifier(id);

    if (test){

 ui->tab_demande->setModel(d.afficher());
 ui->tab_demande_2->setModel(d.afficher());
 ui->tableView->setModel(d.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);




}



void  MainWindow::on_tableView_activated(const QModelIndex &index)

{

    QString val=ui->tableView->model()->data(index).toString();

  /* Connection conn;
    if(!conn.createconnection()){

        qDebug()<<"failed to connect ";
        return ;*
    }

conn.createconnection();*/
    QSqlQuery qry;
    qry.prepare("select * from DEMANDES_ADMINISTRATIVES where iddem ='" +val+"' or nom ='" +val+"' or type ='" +val+"'");

    if (qry.exec())
    {
        while (qry.next())
        {
            ui->le_id_2->setText(qry.value(0).toString());
            ui->le_id_3->setText(qry.value(1).toString());
            ui->le_id_4->setText(qry.value(2).toString());
            //ui->dateEdit_3->setDate(qry.value(3).toDate());



        }
       // conn.closeconnection();
    }
    else
    { QMessageBox::critical(this,tr("error::"),qry.lastError().text());}

}

void MainWindow::on_tab_demande_2_activated(const QModelIndex &index)
{
    QString val=ui->tab_demande_2->model()->data(index).toString();


    QSqlQuery qry;
    qry.prepare("select * from DEMANDES_ADMINISTRATIVES where iddem ='" +val+"' or nom ='" +val+"' or type ='" +val+"'");

    if (qry.exec())
    {
        while (qry.next())
        {
            ui->le_supp_2->setText(qry.value(0).toString());



        }

    }
    else
    { QMessageBox::critical(this,tr("error::"),qry.lastError().text());}

}


void MainWindow::on_pushButton_2_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images Files (*.png *.jpg *.jpeg *.bmp)"));
    if (QString::compare(filename,QString()) != 0)
    {

        QImage pic ;

    bool valid = pic.load(filename);
    if (valid)
    {
        pic = pic.scaledToHeight(ui->label_21->height(),Qt::SmoothTransformation);
        ui->label_21->setPixmap(QPixmap::fromImage(pic));
   }


    else {
        //Error handling
    }
}
}
