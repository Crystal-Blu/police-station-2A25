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
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ret=A.connect_arduino();
        switch (ret) {
        case(0): qDebug() << "arduino is available and connected to :" <<A.getarduino_port_name();
        break ;
        case(1): qDebug() << "arduino is available and not connected to :" <<A.getarduino_port_name();
        break ;
        case(-1): qDebug() << "arduino is not available";

            }
  QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

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
    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();



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
    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

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


        ui->le_cin->clear();
        ui->le_nom->clear();
        ui->lineEdit_16->clear();
        ui->le_adresse->clear();
        ui->dateEdit->clear();
        ui->label_21->clear();


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}



void MainWindow::on_supp_button_clicked()
{

    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();


    int CIN  = ui->le_supp->text().toInt();
    bool test = c1.supprimer(CIN);

    if (test){
        ui->comboBox->setModel(d.afficher_combo());
         ui->comboBox_cin->setModel(d.afficher_combo_2());

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
    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

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

            ui->le_cin_modif->clear();
            ui->le_nom_modif->clear();
            ui->le_prenom_modif->clear();
            ui->le_adresse_modif->clear();
            ui->dateN_modif->clear();
            ui->label_31->clear();

        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);




}

void MainWindow::on_pushButton_Ajouter_2_clicked()
{

    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

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

        ui->comboBox->clear();
        ui->le_nom_2->clear();
        ui->le_type->clear();
        ui->comboBox_cin->clear();
        ui->dateEdit_2->clear();
        ui->le_id->clear();


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}



void MainWindow::on_pushButton_supp_2_clicked()

{
    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

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

    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

    int id=ui->le_id_2->text().toInt();

 int idp=ui->lineEdit_15->text().toInt();

 int cin=ui->lineEdit_14->text().toInt();
    QString nom=ui->le_id_3->text();
    QString type=ui->le_id_4->text();
    QDate DATE_CREATION=ui->dateEdit_3-> date();


    demandes_administratives d(id,idp,cin,nom,type,DATE_CREATION);
    bool test = d.modifier(id);

    if (test){

 ui->tab_demande->setModel(d.afficher());
 ui->tab_demande_2->setModel(d.afficher());
 ui->tableView->setModel(d.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);

        ui->le_id_2->clear();
        ui->lineEdit_15->clear();
        ui->le_id_3->clear();
        ui->le_id_4->clear();
        ui->dateEdit_3->clear();
        ui->lineEdit_14->clear();


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
            ui->dateEdit_3->setDateTime(qry.value(5).toDateTime());







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

    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

    QPdfWriter pdf("C:/Users/asus/OneDrive/Bureau/PdfDEMANDES.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);

                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Requests list");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/asus/OneDrive/Bureau/projetc++/Projetc_/Police.png"));
                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.setPen(Qt::blue);
                                     painter.drawText(200,3300,"IDREQ");
                                     painter.drawText(1900,3300,"NAME");
                                     painter.drawText(3000,3300,"TYPE");
                                     painter.drawText(4000,3300,"DATE OF CREATION");
                                     painter.drawText(6000,3300,"ID_P");
                                     painter.drawText(7000,3300,"IC");



                                     QSqlQuery query;
                                     query.prepare("select * from DEMANDES_ADMINISTRATIVES");
                                     query.exec();
                                     while (query.next())
                                     {
                                         painter.drawText(200,i,query.value(0).toString());
                                         painter.drawText(1900,i,query.value(1).toString());
                                         painter.drawText(3000,i,query.value(2).toString());
                                         painter.drawText(4000,i,query.value(5).toString());
                                         painter.drawText(6000,i,query.value(3).toString());
                                         painter.drawText(7000,i,query.value(4).toString());



                                        i = i +500;
                                     }
                                     int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                         QMessageBox::Yes |  QMessageBox::No);
                                         if (reponse == QMessageBox::Yes)
                                         {
                                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/asus/OneDrive/Bureau/PdfDEMANDES.pdf"));

                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();
    }
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

void MainWindow::on_pb_darkmode_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

    QFile f("C:/Users/asus/OneDrive/Bureau/projetc++/Projetc_/dark/style.qss");

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
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

    QFile f("C:/Users/asus/OneDrive/Bureau/projetc++/Projetc_/darkorange/darkorange.qss");

      if (!f.exists())   {
         qDebug("Unable to set stylesheet, file not found\n");
      }
      else   {
          f.open(QFile::ReadOnly | QFile::Text);
          QTextStream ts(&f);
          setStyleSheet(ts.readAll());}
}

void MainWindow::on_pushButton_9_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
       music->setMedia(QUrl("qrc:/sound/projetc_sound_click.wav"));
       music->play();

    QFile f("C:/Users/asus/OneDrive/Bureau/projetc++/Projetc_/light/style.qss");

       if (!f.exists())   {
          qDebug("Unable to set stylesheet, file not found\n");
       }
       else   {
           f.open(QFile::ReadOnly | QFile::Text);
           QTextStream ts(&f);
           setStyleSheet(ts.readAll());}
}
