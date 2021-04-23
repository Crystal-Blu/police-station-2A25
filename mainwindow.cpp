#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QDateEdit>
#include <QLineEdit>
#include"delits.h"
#include "chart.h"
#include "criminels.h"
#include<QMediaPlayer>
#include<QFileDialog>
#include<QComboBox>
#include"charttype.h"
#include <QPrinter>
#include <QPrintDialog>
#include<QTextDocument>
#include<QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QPdfWriter>
#include<QFile>
#include<QApplication>
#include<QSoundEffect>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //CONTROLE SAISIE ID CRIMINEL

    QRegExp rx("[0-9]{5}");


    QValidator *validator = new QRegExpValidator(rx, this);

    ui->lineEdit_id_c->setValidator(validator);
    ui->lineEdit_ID_cm->setValidator(validator);
    ui->lineEdit_18->setValidator(validator);
    ui->lineEdit_5->setValidator(validator);
    ui->lineEdit_10->setValidator(validator);



    //CONTROLE SAISIE ID DELIT



    QRegExp rx1("[0-9]{4}");
    QValidator *validator1 = new QRegExpValidator(rx, this);
    ui->lineEdit_27->setValidator(validator1);
    ui->lineEdit_26->setValidator(validator1);
    ui->le_mid->setValidator(validator1);
    ui->ledelitid->setValidator(validator1);


//INITIATION AFFICHAGE

    ui->tab_delit1->setModel(D1.afficher());
    ui->tab_delit2->setModel(D1.afficher());
    ui->tab_criminel1->setModel(C1.afficher_c());

    ui->tab_criminel2->setModel(C1.afficher_c());

    //AFFICHAGE NOMBRE CRIMINEL

    QSqlQuery query;
       int numRows= 0;
       query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
       if(query.first())
           numRows = query.value(0).toInt();
       QString numRowsstr=QString::number(numRows);

ui->lineEdit_17->setText(numRowsstr);

//INITIATION MEDIAPLAYER


mMediaPlayer = new QMediaPlayer (this);
connect(mMediaPlayer,&QMediaPlayer ::positionChanged,[&](qint64 pos){
    ui->avance->setValue(pos);
}    );
connect(mMediaPlayer,&QMediaPlayer::durationChanged,[&](qint64 dur) {
    ui->avance->setMaximum(dur);
});


mmMediaPlayer = new QMediaPlayer (this);


}



MainWindow::~MainWindow()
{
    delete ui;
}


//AJOUTER DELIT

void MainWindow::on_pushButton_6_clicked()
{
    int ID_DELIT=ui->ledelitid->text().toInt();
    QString TYPE_DELIT=ui->comboBox->currentText();


    QString DESCRIPTION_DELIT=ui->le_desc_delit->text();
    QDate DATE_DELIT=ui->dateEditdelit->date();
    int ID_CRIMINEL=ui->comboBox_2->currentText().toInt();
    Delits H(ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT,ID_CRIMINEL);
    bool test=H.ajouter();
    if (test){

        ui->tab_delit1->setModel(D1.afficher());
        ui->tab_delit2->setModel(D1.afficher());


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


    }



//SUPPRIMER DELIT

void MainWindow::on_supprimerPb_3_clicked()
{
    int ID_DELIT=ui->lineEdit_26->text().toInt();
    bool test =D1.supprimer(ID_DELIT);

    if (test){

     ui->tab_delit1->setModel(D1.afficher());
     ui->tab_delit2->setModel(D1.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
 QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}


//MODIFIER  DELIT

void MainWindow::on_pushButton_13_clicked()
{
    int ID_DELIT=ui->le_mid->text().toInt();
    QString TYPE_DELIT=ui->comboBox_3->currentText();
    QString DESCRIPTION_DELIT=ui->lineEdit_11->text();
     QDate DATE_DELIT=ui->dateEdit_3->date();
     int ID_CRIMINEL=ui->comboBox_2->currentText().toInt();

     Delits F(ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT,ID_CRIMINEL);
    bool test = F.modifier(ID_DELIT);

    if (test){

 ui->tab_delit1->setModel(F.afficher());
 ui->tab_delit2->setModel(F.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);



}
//AJOUT CRIMINEL
void MainWindow::on_PB_add_c_clicked()
{

        int ID_CRIMINEL=ui->lineEdit_id_c->text().toInt();
        QString NOM_CRIMINEL=ui->lineEdit_nom_c->text() ;
        QString PRENOM_CRIMINEL=ui->lineEdit_prenom_c->text();
        int AGE_CRIMINEL=ui->lineEdit_age_c->text().toInt();
        Criminels C1(ID_CRIMINEL,AGE_CRIMINEL,NOM_CRIMINEL,PRENOM_CRIMINEL);
        bool test=C1.ajouter_c();
        if (test){
            QSqlQuery query;
               int numRows= 0;
               query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
               if(query.first())
                   numRows = query.value(0).toInt();
               QString numRowsstr=QString::number(numRows);

        ui->lineEdit_17->setText(numRowsstr);
            ui->tab_criminel1->setModel(C1.afficher_c());

            ui->tab_criminel2->setModel(C1.afficher_c());

                QMessageBox::information(nullptr,QObject::tr("OK"),
                                         QObject::tr("Ajout effectué\n"
        "Click Cancel to exit"),QMessageBox::Cancel);


            }
            else
                QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}

//SUPPRIMER CRIMINEL


void MainWindow::on_PB_DEL_C_clicked()
{
    int ID_CRIMINEL=ui->lineEdit_18->text().toInt();
    bool test =C1.supprimer_c(ID_CRIMINEL);

    if (test){
        QSqlQuery query;
           int numRows= 0;
           query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
           if(query.first())
               numRows = query.value(0).toInt();
           QString numRowsstr=QString::number(numRows);

    ui->lineEdit_17->setText(numRowsstr);
     ui->tab_criminel1->setModel(C1.afficher_c());
     ui->tab_criminel2->setModel(C1.afficher_c());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
 QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}


//MODIFIER CRIMINEL


void MainWindow::on_PB_mod_c_clicked()
{
    int ID_CRIMINEL=ui->lineEdit_ID_cm->text().toInt();
    QString NOM_CRIMINEL=ui->lineEdit_nom_cm->text();
    QString PRENOM_CRIMINEL=ui->lineEdit_prenom_cm->text();
     int AGE_CRIMINEL=ui->lineEdit_age_cm->text().toInt();

     Criminels C1(ID_CRIMINEL,AGE_CRIMINEL,NOM_CRIMINEL,PRENOM_CRIMINEL);
    bool test = C1.modifier_c(ID_CRIMINEL);

    if (test){

 ui->tab_criminel1->setModel(C1.afficher_c());
 ui->tab_criminel2->setModel(C1.afficher_c());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_pushButton_12_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();

    QSqlQuery query;
    int ID_DELIT=ui->lineEdit_27->text().toInt();

    QString ID_DELITstr=QString::number(ID_DELIT);

    query.exec("SELECT * from DELITS WHERE ID_DELIT  ='"+ID_DELITstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tab_delit2;

        view->setModel(model);
        ui->lineEdit_27->setText("");
}
void MainWindow::on_pushButton_2_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();

    QSqlQuery query;
    int ID_CRIMINEL=ui->lineEdit_5->text().toInt();

    QString ID_CRIMINELstr=QString::number(ID_CRIMINEL);

    query.exec("SELECT * from CRIMINELS WHERE ID_CRIMINEL  ='"+ID_CRIMINELstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tab_criminel2;

        view->setModel(model);
        ui->lineEdit_ID_cm->setText("");
        ui->lineEdit_age_cm->setText("");
        ui->lineEdit_prenom_cm->setText("");
        ui->lineEdit_nom_cm->setText("");

}

void MainWindow::on_pushButton_3_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();


    QSqlQuery query;
    int ID_CRIMINEL=ui->lineEdit_10->text().toInt();

    QString ID_CRIMINELstr=QString::number(ID_CRIMINEL);

    query.exec("SELECT * from CRIMINELS WHERE ID_CRIMINEL  ='"+ID_CRIMINELstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tableView_3;

        view->setModel(model);
        ui->lineEdit_ID_cm->setText("");
}

void MainWindow::on_pushButton_trier_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();

    QSqlQuery query;
    query.exec("SELECT * FROM DELITS ORDER BY TYPE_DELIT");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    QTableView *view =ui->tab_delit1;

       view->setModel(model);
       ui->lineEdit_ID_cm->setText("");



}

void MainWindow::on_pushButton_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();




    QSqlQuery query;
    query.exec("SELECT * FROM DELITS ORDER BY DATE_DELIT");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    QTableView *view =ui->tab_delit1;

       view->setModel(model);
       ui->lineEdit_ID_cm->setText("");

}

void MainWindow::on_pushButton_5_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();

    chart chart;
    chart.setModal(true);
    chart.exec();
}
//music

void MainWindow::on_pushButton_ouvm_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();
   QString filename = QFileDialog :: getOpenFileName(this,"police");
   if (filename.isEmpty()) {return;}
   mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
   mMediaPlayer->setVolume(ui->volume->value());
   on_pushButton_play_clicked();
}

void MainWindow::on_pushButton_play_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();
    mMediaPlayer->play();
}

void MainWindow::on_pushButton_pause_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();
    mMediaPlayer->pause();
}

void MainWindow::on_pushButton_stop_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();
    mMediaPlayer->stop();
}

void MainWindow::on_pushButton_mute_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();
    if(ui->pushButton_mute->text()=="MUTE"){
    mMediaPlayer->setMuted(true);
    ui->pushButton_mute->setText("UNMUTE");
   }else {
       mMediaPlayer->setMuted(false);
       ui->pushButton_mute->setText("MUTE");
}
}

void MainWindow::on_volume_valueChanged(int value)
{

    mMediaPlayer->setVolume(value);
}

void MainWindow::on_PB_load_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();

    QSqlQuery query;
    query.exec("SELECT ID_CRIMINEL FROM CRIMINELS");
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    ui->comboBox_2->setModel(model);
        qDebug() <<(model->rowCount());



}

void MainWindow::on_pushButton_trier_2_clicked()
{       QUrl url ;
        url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

           mmMediaPlayer->setMedia(url);
           mmMediaPlayer->setVolume(50);
           mmMediaPlayer->play();

    charttype charttype;
     charttype.setModal(true);
     charttype.exec();

}

void MainWindow::on_pushButton_4_clicked()
{



    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();

    QPdfWriter pdf("C:/Users/Ilyes/Desktop/Pdfcriminel.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);

                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Criminel");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Ilyes/Desktop/homme.jpg"));
                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.setPen(Qt::blue);
                                     painter.drawText(300,3300,"ID CRIMINEL");
                                     painter.drawText(2300,3300,"AGE");
                                     painter.drawText(4300,3300,"NOM");
                                     painter.drawText(6300,3300,"PRENOM");


                                     QSqlQuery query;
                                     query.prepare("select * from CRIMINELS");
                                     query.exec();
                                     while (query.next())
                                     {
                                         painter.drawText(300,i,query.value(0).toString());
                                         painter.drawText(2300,i,query.value(1).toString());
                                         painter.drawText(4300,i,query.value(2).toString());
                                         painter.drawText(6300,i,query.value(3).toString());



                                        i = i +500;
                                     }
                                     int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                         QMessageBox::Yes |  QMessageBox::No);
                                         if (reponse == QMessageBox::Yes)
                                         {
                                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Ilyes/Desktop/Pdfcriminel.pdf"));

                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();





}
}

void MainWindow::on_pushButton_7_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();

        QFile file("C:/Users/Ilyes/Desktop/Ilyes/Smart_police_station_ilyes/ressources/light/style.qss");

        file.open(QFile::ReadOnly);
        QString styleSheet = QString::fromLatin1(file.readAll());
        ui->label_16->setText("Light Mode");

        // Option 1: Set theme for the inner central widget
        //ui->centralWidget->setStyleSheet(styleSheet);

        // Option 2: Set theme for the entire application
        this->setStyleSheet(styleSheet);
}



/*void MainWindow::on_pushButton_19_clicked()
{
    player->play();
    QFile f("C:/Users/WALID/Desktop/Studies/Projet cpp/dark/style.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_pushButton_20_clicked()
{
    player->play();
    QFile f("C:/Users/WALID/Desktop/Studies/Projet cpp/light/style.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    player->play();
    QFile f("C:/Users/WALID/Desktop/Studies/Projet cpp/DarkOrange/darkorange/darkorange.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
    }
}
*/
void MainWindow::on_pushButton_8_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();
        QFile file("C:/Users/Ilyes/Desktop/Ilyes/Smart_police_station_ilyes/ressources/dark/style.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QString::fromLatin1(file.readAll());
ui->label_16->setText("Dark Mode");
        // Option 1: Set theme for the inner central widget
        //ui->centralWidget->setStyleSheet(styleSheet);

        // Option 2: Set theme for the entire application
        this->setStyleSheet(styleSheet);
}

void MainWindow::on_pushButton_9_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

     mmMediaPlayer->setMedia(url);
     mmMediaPlayer->setVolume(50);
     mmMediaPlayer->play();
        QFile file("C:/Users/Ilyes/Desktop/Ilyes/Smart_police_station_ilyes/ressources/DarkOrange/darkorange.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QString::fromLatin1(file.readAll());
        ui->label_16->setText("Dark orange");

        // Option 1: Set theme for the inner central widget
        //ui->centralWidget->setStyleSheet(styleSheet);

        // Option 2: Set theme for the entire application
        this->setStyleSheet(styleSheet);
}
