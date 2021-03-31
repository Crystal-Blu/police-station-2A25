#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citoyen.h"
#include "connection.h"
#include<QMessageBox>
#include<QPdfWriter>
#include<QSqlQuery>
#include<QSqlError>
#include<QIntValidator>
#include <QValidator>
#include <QDateEdit>
#include<QDateTimeEdit>
#include <QSqlDatabase>
#include<QFileDialog>
#include<QFile>
#include<QImage>
#include <QDebug>
#include <QBuffer>
#include <QVariant>
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
    ui->le_cin->setValidator ( new QIntValidator(0, 99999999, this));

    ui->le_supp->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_supp_2->setValidator ( new QIntValidator(0, 999999, this));
    ui->le_id->setValidator ( new QIntValidator(0, 999999, this));
     ui->le_id_2->setValidator ( new QIntValidator(0, 999999, this));
      ui->le_cin_modif->setValidator ( new QIntValidator(0, 99999999, this));

    ui->tab_citoyen->setModel(C.afficher());
     ui->comboBox->setModel(d.afficher_combo());
      ui->comboBox_cin->setModel(d.afficher_combo_2());
    ui->tab_citoyen_modifier->setModel(C.afficher());
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

void MainWindow::on_pushButton_2_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images Files (*.png *.jpg *.jpeg *.bmp)"));
    C.set_path(filename);
    if (QString::compare(filename,QString()) != 0)
    {

        QImage pic ;

    bool valid = pic.load(filename);
    if (valid)
    {
        pic = pic.scaledToHeight(ui->label_21->height(),Qt::SmoothTransformation);
        qDebug()<<filename;
        ui->label_21->setPixmap(QPixmap::fromImage(pic));




        QByteArray inByteArray;
           QBuffer inBuffer( &inByteArray );
           inBuffer.open( QIODevice::WriteOnly );
           pic.save( &inBuffer, "JPG" );

   }


    else {
        //Error handling
    }
}
}





void MainWindow::on_pushButton_Ajouter_clicked()

{
    int CIN=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->lineEdit_16->text();
    QString adresse=ui->le_adresse->text();
  QByteArray inByteArray /* = ui->label_21->pixmap()-> */;

   QDate DATE_NAISSANCE=ui->dateEdit->date() ;
    QString path=C.get_path();
    Citoyen C(CIN,nom,prenom,adresse,inByteArray,DATE_NAISSANCE,path);
    bool test = C.ajouter();

    if (test){

        ui->comboBox->setModel(d.afficher_combo());
         ui->comboBox_cin->setModel(d.afficher_combo_2());
ui->tab_citoyen_modifier->setModel(C.afficher());
 ui->tab_citoyen->setModel(C.afficher());
 ui->tab_citoyen_2->setModel(C.afficher());
qDebug()<<path;

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

ui->tab_citoyen_modifier->setModel(C.afficher());
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

        int CIN=ui->le_cin_modif->text().toInt();
        QString nom=ui->le_nom_modif->text();
        QString prenom=ui->le_prenom_modif->text();
        QString adresse=ui->le_adresse_modif->text();
        QString path=C.get_path();
     QByteArray inByteArray/* =ui->label_21->setPixmap */;
         QDate DATE_NAISSANCE=ui->dateN_modif->date();







        Citoyen C(CIN,nom,prenom,adresse,inByteArray,DATE_NAISSANCE,path);
        bool test = C.modifier(CIN);

        if (test){
            ui->comboBox->setModel(d.afficher_combo());
             ui->comboBox_cin->setModel(d.afficher_combo_2());
    ui->tab_citoyen_modifier->setModel(C.afficher());
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


     int idp=ui->comboBox->currentText().toInt();
qDebug()<<idp ;

    int cin=ui->comboBox_cin->currentText().toInt();
    QString nom=ui->le_nom_2->text();
    QString type=ui->le_type->text();
    QDate DATE_CREATION=ui->dateEdit_2->date();

     demandes_administratives d(id,idp,cin,nom,type,DATE_CREATION);
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

 int idp=ui->lineEdit_15->text().toInt();

 int cin=ui->lineEdit_14->text().toInt();
    QString nom=ui->le_id_3->text();
    QString type=ui->le_id_4->text();
    QDate DATE_CREATION=ui->dateTimeEdit-> date();


    demandes_administratives d(id,idp,cin,nom,type,DATE_CREATION);
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
    qry.prepare("select * from DEMANDES_ADMINISTRATIVES where iddem ='" +val+"' or nom ='" +val+"' or type ='" +val+"'     ");

    if (qry.exec())
    {
        while (qry.next())
        {
            ui->le_id_2->setText(qry.value(0).toString());
            ui->le_id_3->setText(qry.value(1).toString());
            ui->le_id_4->setText(qry.value(2).toString());
            ui->lineEdit_15->setText(qry.value(3).toString());
            ui->lineEdit_14->setText(qry.value(4).toString());
            ui->dateTimeEdit->setDateTime(qry.value(5).toDateTime());







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






//void MainWindow::on_comboBox_currentIndexChanged(int index)
/*{
     int name = ui->comboBox->currentData().toInt;
}
*/

void MainWindow::on_tab_citoyen_2_activated(const QModelIndex &index)
{
    QString val=ui->tab_citoyen_2->model()->data(index).toString();


    QSqlQuery qry;
    qry.prepare("select * from CITOYENS where cin ='" +val+"' or nom ='" +val+"' or prenom ='" +val+"'");

    if (qry.exec())
    {
        while (qry.next())
        {
            ui->le_supp->setText(qry.value(0).toString());



        }

    }
    else
    { QMessageBox::critical(this,tr("error::"),qry.lastError().text());}

}

void MainWindow::on_tab_citoyen_modifier_activated(const QModelIndex &index)
{


     QString val=ui->tab_citoyen_modifier->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("select * from CITOYENS where cin ='" +val+"' or nom ='" +val+"' or prenom ='" +val+"' or adresse  ='" +val+"'   ");

    if (qry.exec())
    {
        while (qry.next())
        {
            ui->le_cin_modif->setText(qry.value(0).toString());
            ui->le_nom_modif->setText(qry.value(1).toString());
            ui->le_prenom_modif->setText(qry.value(2).toString());
            ui->le_adresse_modif->setText(qry.value(3).toString());
            ui->dateN_modif->setDate(qry.value(5).toDate());



        }
       // conn.closeconnection();
    }
    else
    { QMessageBox::critical(this,tr("error::"),qry.lastError().text());}

}

void MainWindow::on_lineEdit_17_textChanged(const QString &arg1)
{
    if(ui->rb_cin->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM CITOYENS WHERE cin LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tab_citoyen_modifier->setModel(model);
            qDebug() <<(model->rowCount());
        }


    if(ui->rb_nom->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM CITOYENS WHERE nom LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tab_citoyen_modifier->setModel(model);
            qDebug() <<(model->rowCount());
        }


    if(ui->rb_date_naissance->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM CITOYENS WHERE DATE_NAISSANCE LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tab_citoyen_modifier->setModel(model);
            qDebug() <<(model->rowCount());
        }
}


void MainWindow::on_pushButton_4_clicked()
{
    int width = 0;
        int height = 0;

      ui->tab_demande->resizeColumnsToContents();
        ui->tab_demande->resizeRowsToContents();

        const int columnCnt = ui->tab_demande->model()->columnCount();
        for( int i = 0; i < columnCnt; ++i )
        {
            width += ui->tab_demande->columnWidth(i) ;
        }
       width=width*2;

        const int rowCnt = ui->tab_demande->model()->rowCount();
        for( int i = 0; i < rowCnt; ++i )
        {
            height += ui->tab_demande->rowHeight(i)  ;
        }
        height=height*2;

        ui->tab_demande->setFixedSize(width, height);

        QPrinter printer;

        ui->tab_demande->render(&printer);

        ui->tab_demande->setFixedSize(631, 281);
}

void MainWindow::on_tab_citoyen_activated(const QModelIndex &index)
{
    QString val=ui->tab_citoyen->model()->data(index).toString();


    QSqlQuery qry;
    qry.prepare("select * from CITOYENS where cin ='" +val+"' or nom ='" +val+"' or prenom ='" +val+"'");

    if (qry.exec())
    {
        while (qry.next())
        {
            QPixmap pix(QPixmap(qry.value(4).toString()));

            ui->pic->setPixmap (pix.scaled (91,111,Qt::KeepAspectRatio));

        }

    }
    else
    { QMessageBox::critical(this,tr("error::"),qry.lastError().text());}
}


void MainWindow::on_pushButton_3_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images Files (*.png *.jpg *.jpeg *.bmp)"));
    C.set_path(filename);
    if (QString::compare(filename,QString()) != 0)
    {

        QImage pic ;

    bool valid = pic.load(filename);
    if (valid)
    {
        pic = pic.scaledToHeight(ui->label_31->height(),Qt::SmoothTransformation);
        qDebug()<<filename;
        ui->label_31->setPixmap(QPixmap::fromImage(pic));




        QByteArray inByteArray;
           QBuffer inBuffer( &inByteArray );
           inBuffer.open( QIODevice::WriteOnly );
           pic.save( &inBuffer, "JPG" );

}
}}

void MainWindow::on_lineEdit_18_textChanged(const QString &arg1)
{
    if(ui->rb_cin_2->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM CITOYENS WHERE cin LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tab_citoyen->setModel(model);
            qDebug() <<(model->rowCount());
        }


    if(ui->rb_nom_2->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM CITOYENS WHERE nom LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tab_citoyen->setModel(model);
            qDebug() <<(model->rowCount());
        }


    if(ui->rb_date_naissance_2->isChecked())
        {
            QSqlQuery query;
            QSqlQueryModel * model=new QSqlQueryModel();
            query.prepare("SELECT * FROM CITOYENS WHERE DATE_NAISSANCE LIKE :surname");
            query.bindValue(":surname", QString("%%1%").arg(arg1));
            query.exec();
            model->setQuery(query);
            ui->tab_citoyen->setModel(model);
            qDebug() <<(model->rowCount());
        }
}