#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QTextStream>
#include <QSqlQuery>
#include <QFile>
#include <QSqlQueryModel>
#include "vehicule_modifier_window.h"
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>
#include <QSqlDriver>
#include <QTimer>
#include "arduino.h"

QString Affichagevehicule_Query="select * from vehicules",groupebyvehi="",Affichagevehicule_Query_f=Affichagevehicule_Query+groupebyvehi;
QString AffichageEq_Query="select * from equipements",groupbyeq="",Affichageeq_Query_f=AffichageEq_Query+groupbyeq;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    int ret=A.connect_arduino();
            switch (ret)
            {
            case(0): qDebug() << "arduino is available and connected to :" <<A.getarduino_port_name();
            break ;
            case(1): qDebug() << "arduino is available and not connected to :" <<A.getarduino_port_name();
            break ;
            case(-1): qDebug() << "arduino is not available";

                }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
        {

        }
    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(check_voiture_repare()));
        connect(timer, SIGNAL(timeout()), this, SLOT(check_equipements_number()));
        connect(timer, SIGNAL(timeout()), this, SLOT(check_vehicules_number()));
        timer->start(15000);

    remplir_equipements();
    remplir_vehi();
    mySystemTrayIcon = new QSystemTrayIcon(this);
    mySystemTrayIcon->setIcon(QIcon("C:/Users/WALID/Desktop/Studies/Projet cpp/Police.png"));
    mySystemTrayIcon->setVisible(true);
    player->setMedia(QUrl::fromLocalFile("C:/Users/WALID/Desktop/Studies/Projet cpp/click.wav"));
    player->setVolume(100);
    ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
    ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
    ui->tableView_4->setModel(R.Afficher_rep());
    ui->lineEdit_7->setValidator ( new QIntValidator(0, 999999999, this));
    ui->lineEdit_7->setMaxLength(20);
    ui->Matricule_eq_edit->setValidator ( new QIntValidator(0, 999999999, this));
    ui->Matricule_eq_edit->setMaxLength(20);
    ui->type_edit->setMaxLength(20);
    ui->MatriculeEdit->setValidator ( new QIntValidator(0, 999999999, this));
    ui->modeleEdit->setMaxLength(20);
    ui->idpedit->setValidator ( new QIntValidator(0, 999999999, this));
    ui->MatriculeEdit_2->setValidator ( new QIntValidator(0, 999999999, this));
    ui->idreparation->setValidator ( new QIntValidator(0, 999999999, this));
    ui->type_reparation->setMaxLength(20);
    remplir();

};
void MainWindow::print_test()
{
    qDebug()<<"timer";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    player->play();
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);

}

void MainWindow::on_ajouter_clicked()
{
    player->play();
    bool test;
    int matricule=ui->MatriculeEdit->text().toInt();
    QString modele=ui->modeleEdit->text();
    int idp=ui->idpedit->text().toInt();
    QDate date_a=ui->dateEdit->date();
    vehicule Veh(matricule,modele,date_a,idp);
    test=Veh.ajouter_vehicule();
    if (test)
    {
         ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
        mySystemTrayIcon ->showMessage(tr("Ajout Effectué avec Succé"),tr("Vehicule Ajouté à la base de donnée"));
    }
    if (!test)
    {
        mySystemTrayIcon ->showMessage(tr("Error"),tr("Vehicule non Ajouté"));
    }

}

void MainWindow::on_Refresh_clicked()
{
    player->play();
    ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
}

int MainWindow::on_Vehicule_table_activated(const QModelIndex &index)
{
    player->play();
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
    player->play();
    int matricule=ui->matslected->text().toInt();
    V.delete_vehicule(matricule);
     ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
}

void MainWindow::on_Modif_btton_clicked()
{
    player->play();
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
    player->play();
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
    player->play();
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

void MainWindow::on_pushButton_9_clicked()
{
    player->play();
    bool test;
    int id=ui->lineEdit_7->text().toInt();
    int matricule=ui->Matricule_eq_edit->text().toInt();
    QString type_eq=ui->type_edit->text();
    Equipements EQ(id,matricule,type_eq);
    test=EQ.ajouter_Equipements();
    if (test)
    {
         ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
       mySystemTrayIcon ->showMessage(tr("Ajout Effectué avec succé"),tr("Equipement ajoutée"));
    }
    if (!test)
    {
        mySystemTrayIcon ->showMessage(tr("Erreur"),tr("Equipements non ajoutée"));
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    player->play();
    ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
}

int MainWindow::on_Equipemen_table_activated(const QModelIndex &index)
{
    player->play();
    QString val=ui->Equipemen_table->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare( " select * from Equipements where Ideqp ='"+val+"'  "   );
        if(qry.exec( ))
        {
            while(qry.next())

        {
                int id=qry.value(0).toInt();
                int mat=qry.value(1).toInt();
                QString typeq=qry.value(2).toString();
                ui->lineEdit_6->setText(qry.value(0).toString());
                ui->lineEdit_8->setText(qry.value(1).toString());
                ui->lineEdit_9->setText(qry.value(2).toString());
                ui->pushButton_11->setEnabled(true);
                ui->pushButton_10->setEnabled(true);
                return id;
        }

        }
        else
        {
          QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("clickez sur le id.\n" "Clic ok to exit."),QMessageBox::Ok);

        }
}

void MainWindow::on_pushButton_11_clicked()
{
    player->play();
    int id=ui->lineEdit_6->text().toInt();
    E.delete_Equipments(id);
     ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
}


void MainWindow::on_pushButton_10_clicked()
{
    player->play();
    bool test;
    int id=ui->lineEdit_6->text().toInt();
    int matricule=ui->lineEdit_8->text().toInt();
    QString type_eq=ui->lineEdit_9->text();
    Equipements EQ(id,matricule,type_eq);
    test=EQ.modifier_Equipments();
    if (test)
    {
         ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout Effectué avec succées \n"), QMessageBox::Ok);
    }
    if (!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),QObject::tr("Ajout Non Effectué \n"), QMessageBox::Ok);
    }
}

void MainWindow::on_Assign_Police_clicked()
{
    player->play();
     ui->tabWidget->setCurrentWidget(ui->tab_7);
     ui->tabWidget_3->setCurrentWidget(ui->tab_15);
    QString mat=ui->matslected->text();
    ui->Matricule_eq_edit->setText(mat); 
}




QSqlQueryModel *MainWindow::get_policiers()
{

}

void MainWindow::on_pushButton_15_clicked()
{
    player->play();
    ui->tableView_4->setModel(R.Afficher_rep());
}

void MainWindow::on_tableView_4_activated(const QModelIndex &index)
{
    player->play();
    QString val=ui->tableView_4->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare( "select * from demande_reparation where id_demande="+val+"  " );
        if(qry.exec( ))
        {
            while(qry.next())

        {
                QString Desc=qry.value(3).toString();
                ui->textBrowser->setText(Desc);
                ui->lineEdit_5->setText(qry.value(1).toString());
                ui->pushButton_18->setEnabled(true);
                return ;
        }

        }
        else
        {
          QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("clickez sur le ID.\n" "Clic ok to exit."),QMessageBox::Ok);

        }
}
void MainWindow::on_Demande_rep_clicked()
{
    player->play();
    ui->tabWidget->setCurrentWidget(ui->tab_6);
    ui->tabWidget_4->setCurrentWidget(ui->tab_19);
    QString mat=ui->matslected->text();
    ui->MatriculeEdit_2->setText(mat);
}

void MainWindow::on_ajouter_2_clicked()
{
    player->play();
    bool test;
    int mat=ui->MatriculeEdit_2->text().toInt();
    int id=ui->idreparation->text().toInt();
    QString type=ui->type_reparation->text();
    QString Desc=ui->textEdit->toPlainText();
    Reparations repa(id,mat,type,Desc);
    qDebug()<<repa.get_desc();
    qDebug()<<repa.get_type();
    qDebug()<<repa.get_id_rep();
    qDebug()<<repa.get_matricule();
    test=repa.ajouter_rep();
    if (test)
    {
         ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
        mySystemTrayIcon ->showMessage(tr("Ajout Effectué avec succé"),tr("Demande de reparation ajoutée"));
    }
    if (!test)
    {
        mySystemTrayIcon ->showMessage(tr("Erreur"),tr("Demande de reparation non ajoutée"));
    }
}

void MainWindow::on_pushButton_18_clicked()
{
    player->play();
    bool test;
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Alert", "Etes vous sure de votre action ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          qDebug() << "Yes was clicked";
         test= R.care_repared (ui->lineEdit_5->text().toInt());
         if (test)
         {
              ui->tableView->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
             QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout Effectué avec succées \n"), QMessageBox::Ok);
         }
         if (!test)
         {
             QMessageBox::critical(nullptr, QObject::tr("OK"),QObject::tr("Ajout Non Effectué \n"), QMessageBox::Ok);
         }
        }
      else {
          qDebug() << "Yes was *not* clicked";
        }

}

void MainWindow::on_pushButton_16_clicked()
{
    player->play();
    R.delete_rep(ui->lineEdit_5->text().toInt());
}



void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{

    if (ui->recherche->currentIndex()==0)
    {
        Affichagevehicule_Query="select * from vehicules where matricule LIKE '"+QString("%%1%").arg(arg1)+"' ";

    }
    if (ui->recherche->currentIndex()==1)
    {
        Affichagevehicule_Query="select * from vehicules where NOM_MARQUE LIKE '"+QString("%%1%").arg(arg1)+"' ";

    }
    if (ui->recherche->currentIndex()==2)
    {
        Affichagevehicule_Query="select * from vehicules where IDP LIKE '"+QString("%%1%").arg(arg1)+"' ";

    }
    updateaffichagevehicule();



}
void MainWindow::updateaffichagevehicule()
{

    if (ui->radioButton_15->isChecked())
    {
         groupebyvehi="ORDER BY matricule ASC ";
    }
    if (ui->radioButton_18->isChecked())
    {
         groupebyvehi="ORDER BY matricule DESC ";
    }
    if (ui->radioButton_17->isChecked())
    {
        groupebyvehi="ORDER BY NOM_MARQUE ASC ";
    }
    if (ui->radioButton_16->isChecked())
    {
         groupebyvehi="ORDER BY NOM_MARQUE DESC ";
    }
    if (ui->radioButton_13->isChecked())
    {
         groupebyvehi="ORDER BY DATE_ACHAT ASC ";
    }
    if (ui->radioButton_14->isChecked())
    {
         groupebyvehi="ORDER BY DATE_ACHAT DESC ";
    }
    if (ui->radioButton_21->isChecked())
    {
         groupebyvehi="ORDER BY IDP ASC ";
    }
    if (ui->radioButton_22->isChecked())
    {
         groupebyvehi="ORDER BY IDP DESC ";
    }
    if (ui->radioButton_9->isChecked())
    {
        groupebyvehi="";
    }
    Affichagevehicule_Query_f=Affichagevehicule_Query+groupebyvehi;
     ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
    qDebug()<<Affichagevehicule_Query_f;
}



void MainWindow::on_pushButton_14_clicked()
{
    player->play();
    ui->lineEdit_3->clear();
    Affichagevehicule_Query_f="select * from vehicules ";
}

void MainWindow::on_radioButton_15_clicked()
{
    player->play();
   if(ui->lineEdit_3->text()=="")
    Affichagevehicule_Query="select * from vehicules ";

    updateaffichagevehicule();
}


void MainWindow::on_radioButton_18_clicked()
{
    player->play();
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_17_clicked()
{
    player->play();
    player->play();
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_16_clicked()
{
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_13_clicked()
{
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_14_clicked()
{
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_21_clicked()
{
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_22_clicked()
{
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_9_clicked()
{
    player->play();
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_7_clicked()
{
    player->play();
    if(ui->lineEdit_2->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_10_clicked()
{
    player->play();
    if(ui->lineEdit_2->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_8_clicked()
{
    player->play();
    if(ui->lineEdit_2->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_11_clicked()
{
    player->play();
    if(ui->lineEdit_2->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}



void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (ui->comboBox->currentIndex()==0)
    {
        AffichageEq_Query="select * from Equipements where matricule LIKE '"+QString("%%1%").arg(arg1)+"' ";

    }
    if (ui->comboBox->currentIndex()==1)
    {
        AffichageEq_Query="select * from Equipements where type LIKE '"+QString("%%1%").arg(arg1)+"' ";

    }
    updateaffichageeq();
}
void MainWindow::updateaffichageeq()
{
    if (ui->radioButton_7->isChecked())
    {
         groupbyeq="ORDER BY matricule ASC ";
    }
    if (ui->radioButton_10->isChecked())
    {
         groupbyeq="ORDER BY matricule DESC ";
    }
    if (ui->radioButton_8->isChecked())
    {
         groupbyeq="ORDER BY type ASC ";
    }
    if (ui->radioButton_11->isChecked())
    {
         groupbyeq="ORDER BY type DESC ";
    }
    Affichageeq_Query_f=AffichageEq_Query+groupbyeq;
     ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
    qDebug()<<Affichageeq_Query_f;
}

void MainWindow::on_pushButton_19_clicked()
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

void MainWindow::on_pushButton_24_clicked()
{
    player->play();
    setStyleSheet("");
}

void MainWindow::on_pushButton_25_clicked()
{
    player->play();
    QPdfWriter pdf("C:/Users/WALID/Desktop/Pdfvehicules.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);
                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Vehicules");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/WALID/Desktop/Studies/Projet cpp/vehicules.jpg"));
                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.setPen(Qt::blue);
                                     painter.drawText(300,3300,"Nom De Marque");
                                     painter.drawText(2300,3300,"Matricule");
                                     painter.drawText(4300,3300,"Date d'achat");
                                     painter.drawText(6300,3300,"IDP");
                                     QSqlQuery query;
                                     query.prepare("select * from VEHICULES");
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
                                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/WALID/Desktop/Pdfvehicules.pdf"));
                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();
    }
}

void MainWindow::on_pushButton_26_clicked()
{
    player->play();
    QPdfWriter pdf("C:/Users/WALID/Desktop/Pdfequipements.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);
                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Vehicules");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/WALID/Desktop/Studies/Projet cpp/equipements.jpg"));
                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.setPen(Qt::blue);
                                     painter.drawText(300,3300,"ID");
                                     painter.drawText(2300,3300,"Matricule");
                                     painter.drawText(4300,3300,"TYPE");
                                     QSqlQuery query;
                                     query.prepare("select * from EQUIPEMTS");
                                     query.exec();
                                     while (query.next())
                                     {
                                         painter.drawText(300,i,query.value(0).toString());
                                         painter.drawText(2300,i,query.value(1).toString());
                                         painter.drawText(4300,i,query.value(2).toString());
                                        i = i +500;
                                     }
                                     int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                         QMessageBox::Yes |  QMessageBox::No);
                                         if (reponse == QMessageBox::Yes)
                                         {
                                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/WALID/Desktop/Pdfequipements.pdf"));
                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();
}
}


void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    if (ui->lineEdit_7->text()!=""&& ui->Matricule_eq_edit->text()!="" && ui->type_edit->text()!="")
    {
        ui->pushButton_9->setEnabled(true);
    }
    else
    {
        ui->pushButton_9->setEnabled(false);
    }
}

void MainWindow::on_Matricule_eq_edit_textChanged(const QString &arg1)
{
    if (ui->lineEdit_7->text()!=""&& ui->Matricule_eq_edit->text()!="" && ui->type_edit->text()!="")
    {
        ui->pushButton_9->setEnabled(true);
    }
    else
    {
        ui->pushButton_9->setEnabled(false);
    }
}

void MainWindow::on_type_edit_textChanged(const QString &arg1)
{
    if (ui->lineEdit_7->text()!=""&& ui->Matricule_eq_edit->text()!="" && ui->type_edit->text()!="")
    {
        ui->pushButton_9->setEnabled(true);
    }
    else
    {
        ui->pushButton_9->setEnabled(false);
    }
}

void MainWindow::on_MatriculeEdit_2_textChanged(const QString &arg1)
{
    if (ui->MatriculeEdit_2->text()!=""&& ui->idreparation->text()!="" && ui->type_reparation->text()!="" && ui->textEdit->toPlainText()!="")
    {
        ui->ajouter_2->setEnabled(true);
    }
    else
    {
        ui->ajouter_2->setEnabled(false);
    }
}

void MainWindow::on_idreparation_textChanged(const QString &arg1)
{
    if (ui->MatriculeEdit_2->text()!=""&& ui->idreparation->text()!="" && ui->type_reparation->text()!="" && ui->textEdit->toPlainText()!="")
    {
        ui->ajouter_2->setEnabled(true);
    }
    else
    {
        ui->ajouter_2->setEnabled(false);
    }
}

void MainWindow::on_type_reparation_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->MatriculeEdit_2->text()!=""&& ui->idreparation->text()!="" && ui->type_reparation->text()!="" && ui->textEdit->toPlainText()!="")
    {
        ui->ajouter_2->setEnabled(true);
    }
    else
    {
        ui->ajouter_2->setEnabled(false);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    if (ui->MatriculeEdit_2->text()!=""&& ui->idreparation->text()!="" && ui->type_reparation->text()!="" && ui->textEdit->toPlainText()!="")
    {
        ui->ajouter_2->setEnabled(true);
    }
    else
    {
        ui->ajouter_2->setEnabled(false);
    }
}

void MainWindow::on_MatriculeEdit_textChanged(const QString &arg1)
{
    if (ui->MatriculeEdit->text()!=""&& ui->modeleEdit->text()!="" && ui->idpedit->text()!="")
    {
        ui->ajouter->setEnabled(true);
    }
    else
    {
        ui->ajouter->setEnabled(false);
    }
}

void MainWindow::on_modeleEdit_textChanged(const QString &arg1)
{
    if (ui->MatriculeEdit->text()!=""&& ui->modeleEdit->text()!="" && ui->idpedit->text()!="")
    {
        ui->ajouter->setEnabled(true);
    }
    else
    {
        ui->ajouter->setEnabled(false);
    }
}

void MainWindow::on_idpedit_textChanged(const QString &arg1)
{
    if (ui->MatriculeEdit->text()!=""&& ui->modeleEdit->text()!="" && ui->idpedit->text()!="")
    {
        ui->ajouter->setEnabled(true);
    }
    else
    {
        ui->ajouter->setEnabled(false);
    }
}

void MainWindow::on_pushButton_27_clicked()
{
    mySystemTrayIcon ->showMessage(tr("bruh"),tr("bruh"));
}

void MainWindow::check_voiture_repare()
{
    int check=0;
    QSqlQuery query;
    query.prepare("select count(D.id_demande) from demande_reparation D natural join vehicules V where V.IDP=:id AND D.repare='OUI'");
    query.bindValue(":id",this->id_policier);
    query.exec();
    qDebug()<<"1";
    while(query.next())
    {
        if (count<query.value(0).toInt())
        {
            mySystemTrayIcon ->showMessage(tr("Reparation Effectué"),tr("Une de vos voitures à été réparé veuillez supprimer la demande"));


        }
        count=query.value(0).toInt();
    }


}
void MainWindow::remplir()
{
    {
        int check=0;
        QSqlQuery query;
        query.prepare("select count(D.id_demande) from demande_reparation D natural join vehicules V where V.IDP=:id AND D.repare='OUI'");
        query.bindValue(":id",this->id_policier);
        query.exec();
        qDebug()<<"1";
        while(query.next())
        {
            count=query.value(0).toInt();

        }
        qDebug()<<count;
    }
}

void MainWindow::check_vehicules_number()
{
    QSqlQuery query;
    query.prepare("select count(*) from vehicules");
    query.exec();
    while(query.next())
    {
        if (count_vehicules!=query.value(0).toInt())
        {
            mySystemTrayIcon ->showMessage(tr("Table Vehicules modifiée"),tr("Des modifications ont été éffectuées sur la table des Vehicules"));


        }
        count_vehicules=query.value(0).toInt();


    }



}
void MainWindow::check_equipements_number()
{
    QSqlQuery query;
    query.prepare("select count(*) from equipements");
    query.exec();
    while(query.next())
    {
        if (count_equipements!=query.value(0).toInt())
        {
            mySystemTrayIcon ->showMessage(tr("Table Equipements modifiée"),tr("Des modifications ont été éffectuées sur la table des equipements"));


        }
        count_equipements=query.value(0).toInt();


    }

}

void MainWindow::remplir_vehi()
{
    {
        int check=0;
        QSqlQuery query;
        query.prepare("select count(*) from vehicules");
        query.exec();
        while(query.next())
        {
            count_vehicules=query.value(0).toInt();

        }

    }
}
void MainWindow::remplir_equipements()
{
    {
        int check=0;
        QSqlQuery query;
        query.prepare("select count(*) from vehicules");
        query.exec();
        while(query.next())
        {
            count_vehicules=query.value(0).toInt();

        }


    }
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_20);
}

void MainWindow::update_label()
{
    QString Message;
    int job;
    data=A.read_from_arduino();
    for (int i=0;i<data.length();i++)
    {
        code=code+data[i];
    }
    if (code.contains("\r\n"))
    {
        Message="Carte RFID introuvable dans la base de données";
        code.remove("\r\n");
        QSqlQuery qry;
        qry.prepare( " select * from policier where CODE =:code");
        qry.bindValue(":code",code);
        if(qry.exec( ))
        {
            while(qry.next())

        {
                job=qry.value(6).toInt();
                if (qry.value(6)==0)
                 Message="Le Policier : "+qry.value(1).toString()+" "+qry.value(2).toString()+" ID = "+qry.value(0).toString()+" Grade: "+qry.value(3).toString()+" vient d'entrer !";
                else if (qry.value(6)==1)
                 Message="Le Policier : "+qry.value(1).toString()+" "+qry.value(2).toString()+" ID = "+qry.value(0).toString()+" Grade: "+qry.value(3).toString()+" vient de rentrer !";


        }
        }
            if (job==0)
        qry.prepare( " UPDATE policier set on_job=1 where CODE =:code");
            else
            qry.prepare( " UPDATE policier set on_job=0 where CODE =:code");
        qry.bindValue(":code",code);
        qry.exec( );
        mySystemTrayIcon ->showMessage(tr("Alerte"),tr(Message.toStdString().c_str()));
        code="";
    }
}
