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
    ui->label_4->setText(QString::number(volume)+"%");
    int ret=A.connect_arduino();
            switch (ret)
            {
            case(0): qDebug() << "arduino is available and connected to :" <<A.getarduino_port_name();
                ui->label_24->setText("Arduino is available and connected");
                ui->label_24->setStyleSheet("QLabel {color : green; }");
                arduino_connected=1;
            break ;
            case(1): qDebug() << "arduino is available and not connected to :" <<A.getarduino_port_name();
                if (arduino_connected==0)
               { ui->label_24->setText("Arduino is available and not connected");
                ui->label_24->setStyleSheet("QLabel {color : yellow; }");}
            break ;
            case(-1): qDebug() << "arduino is not available";
                ui->label_24->setText("Arduino is not available");
                ui->label_24->setStyleSheet("QLabel {color : red; }");
                arduino_connected=0;
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
    player->setMedia(QUrl::fromLocalFile("C:/Users/xDrais/Desktop/police-station-2A25-vehicules-equipements/click.wav"));
    player->setVolume(volume);
    ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
    ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
    ui->tableView_reparations->setModel(R.Afficher_rep());
    ui->id_eq_edit->setValidator ( new QIntValidator(0, 999999999, this));
    ui->id_eq_edit->setMaxLength(20);
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
    QDate date_a=ui->dateEdit_vehicules->date();
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








void MainWindow::on_ajouter_equipement_clicked()
{
    player->play();
    bool test;
    int id=ui->id_eq_edit->text().toInt();
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
                ui->selected_id_epuip->setText(qry.value(0).toString());
                ui->selected_matricule_eq->setText(qry.value(1).toString());
                ui->selected_type_eq->setText(qry.value(2).toString());
                ui->supprimer_equipements->setEnabled(true);
                ui->modifier_equip->setEnabled(true);
                return id;
        }

        }
        else
        {
          QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("clickez sur le id.\n" "Clic ok to exit."),QMessageBox::Ok);

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
    ui->tableView_reparations->setModel(R.Afficher_rep());
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



void MainWindow::on_cancelbtnvehicules_clicked()
{
    player->play();
    ui->rechercher_vehicule_edit->clear();
    Affichagevehicule_Query_f="select * from vehicules ";
}

void MainWindow::on_radioButton_15_clicked()
{
    player->play();
   if(ui->rechercher_vehicule_edit->text()=="")
    Affichagevehicule_Query="select * from vehicules ";

    updateaffichagevehicule();
}


void MainWindow::on_radioButton_18_clicked()
{
    player->play();
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_17_clicked()
{
    player->play();
    player->play();
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_16_clicked()
{
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_13_clicked()
{
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_14_clicked()
{
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_21_clicked()
{
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_22_clicked()
{
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_9_clicked()
{
    player->play();
    if(ui->rechercher_vehicule_edit->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_7_clicked()
{
    player->play();
    if(ui->recherche_eq->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_10_clicked()
{
    player->play();
    if(ui->recherche_eq->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_8_clicked()
{
    player->play();
    if(ui->recherche_eq->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_11_clicked()
{
    player->play();
    if(ui->recherche_eq->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}



void MainWindow::on_recherche_eq_textChanged(const QString &arg1)
{
    if (ui->comboBox_eq->currentIndex()==0)
    {
        AffichageEq_Query="select * from Equipements where matricule LIKE '"+QString("%%1%").arg(arg1)+"' ";

    }
    if (ui->comboBox_eq->currentIndex()==1)
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
    QFile f("C:/Users/xDrais/Desktop/police-station-2A25-vehicules-equipements/dark/style.qss");

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
    QFile f("C:/Users/xDrais/Desktop/police-station-2A25-vehicules-equipements/light/style.qss");

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
    QFile f("C:/Users/xDrais/Desktop/police-station-2A25-vehicules-equipements/DarkOrange/darkorange/darkorange.qss");

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



void MainWindow::on_id_eq_edit_textChanged(const QString &arg1)
{
    if (ui->id_eq_edit->text()!=""&& ui->Matricule_eq_edit->text()!="" && ui->type_edit->text()!="")
    {
        ui->ajouter_equipement->setEnabled(true);
    }
    else
    {
        ui->ajouter_equipement->setEnabled(false);
    }
}

void MainWindow::on_Matricule_eq_edit_textChanged(const QString &arg1)
{
    if (ui->id_eq_edit->text()!=""&& ui->Matricule_eq_edit->text()!="" && ui->type_edit->text()!="")
    {
        ui->ajouter_equipement->setEnabled(true);
    }
    else
    {
        ui->ajouter_equipement->setEnabled(false);
    }
}

void MainWindow::on_type_edit_textChanged(const QString &arg1)
{
    if (ui->id_eq_edit->text()!=""&& ui->Matricule_eq_edit->text()!="" && ui->type_edit->text()!="")
    {
        ui->ajouter_equipement->setEnabled(true);
    }
    else
    {
        ui->ajouter_equipement->setEnabled(false);
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
                {
                    A.write_to_arduino("0");
                 Message="Le Policier : "+qry.value(1).toString()+" "+qry.value(2).toString()+" ID = "+qry.value(0).toString()+" Grade: "+qry.value(3).toString()+" vient d'entrer !";
                }
                else if (qry.value(6)==1)
                {
                 A.write_to_arduino("1");
                 Message="Le Policier : "+qry.value(1).toString()+" "+qry.value(2).toString()+" ID = "+qry.value(0).toString()+" Grade: "+qry.value(3).toString()+" vient de rentrer !";
                }

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

void MainWindow::on_rechercher_vehicule_edit_textChanged(const QString &arg1)
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



void MainWindow::on_Chech_matricule_vehi_clicked()
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

void MainWindow::on_check_idp_vehi_clicked()
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

void MainWindow::on_tableView_reparations_activated(const QModelIndex &index)
{
    player->play();
    QString val=ui->tableView_reparations->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare( "select * from demande_reparation where id_demande="+val+"  " );
        if(qry.exec( ))
        {
            while(qry.next())

        {
                QString Desc=qry.value(3).toString();
                ui->textBrowser->setText(Desc);
                ui->id_selected_reparation->setText(qry.value(1).toString());
                ui->declarerepare->setEnabled(true);
                return ;
        }

        }
        else
        {
          QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("clickez sur le ID.\n" "Clic ok to exit."),QMessageBox::Ok);

        }
}

void MainWindow::on_declarerepare_clicked()
{
    player->play();
    bool test;
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Alert", "Etes vous sure de votre action ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          qDebug() << "Yes was clicked";
         test= R.care_repared (ui->id_selected_reparation->text().toInt());
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
      else {
          qDebug() << "Yes was *not* clicked";
        }
}

void MainWindow::on_supprimer_reparation_clicked()
{
    player->play();
        R.delete_rep(ui->id_selected_reparation->text().toInt());
}





void MainWindow::on_Print_pdf_vehicules_clicked()
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

void MainWindow::on_print_pdf_equipements_clicked()
{
    player->play();
    QPdfWriter pdf("C:/Users/WALID/Desktop/Pdfequipements.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);
                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Equipements");
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
                                     query.prepare("select * from EQUIPEMENTS");
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

void MainWindow::on_refresh_equipements_clicked()
{
    player->play();
    ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
}

void MainWindow::on_supprimer_equipements_clicked()
{
    player->play();
    int id=ui->selected_id_epuip->text().toInt();
    E.delete_Equipments(id);
     ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
}

void MainWindow::on_modifier_equip_clicked()
{
    player->play();
    bool test;
    int id=ui->selected_id_epuip->text().toInt();
    int matricule=ui->selected_matricule_eq->text().toInt();
    QString type_eq=ui->selected_type_eq->text();
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

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    volume=ui->horizontalSlider->value();
    ui->label_4->setText(QString::number(volume)+"%");
    player->setVolume(volume);
    ui->checkBox->setChecked(false);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked())
    {
        player->setVolume(0);
        ui->label_4->setText("0%");
    }
    else
    {
        player->setVolume(volume);
        ui->label_4->setText(QString::number(volume)+"%");
    }
}

void MainWindow::on_test_clicked()
{
    int ret=A.connect_arduino();
            switch (ret)
            {
            case(0): qDebug() << "arduino is available and connected to :" <<A.getarduino_port_name();
                ui->label_24->setText("Arduino is available and connected");
                ui->label_24->setStyleSheet("QLabel {color : green; }");
                arduino_connected=1;
            break ;
            case(1): qDebug() << "arduino is available and not connected to :" <<A.getarduino_port_name();
                if (arduino_connected==0)
               { ui->label_24->setText("Arduino is available and not connected");
                ui->label_24->setStyleSheet("QLabel {color : yellow; }");}
            break ;
            case(-1): qDebug() << "arduino is not available";
                ui->label_24->setText("Arduino is not available");
                ui->label_24->setStyleSheet("QLabel {color : red; }");
                arduino_connected=0;
                }
            QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
            {

            }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (ui->checkBox_2->isChecked())
    mySystemTrayIcon->setVisible(false);
    else
        mySystemTrayIcon->setVisible(true);
}


void MainWindow::on_pb_addpolice_clicked()
{
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
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
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
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
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
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
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();

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
        ui->tabWidget_5->setCurrentIndex(ui->tabWidget_5->count()-1);

}

}
else
{
  QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("selection non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

}
}



void MainWindow::on_pb_mission_clicked()
{
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
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
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();*/
    player->play();
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
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
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
   /*QMediaPlayer * music = new QMediaPlayer();
   music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
   music->play();
*/
    player->play();
 ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);
}

void MainWindow::on_pb_missionstaketoadd_clicked()
{
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
 ui->tabWidget_5->setCurrentIndex(ui->tabWidget_5->count()-2);
}

void MainWindow::on_pb_missionadd_clicked()
{
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
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
    /*
QMediaPlayer * music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
music->play();
*/
    player->play();
QPdfWriter pdf("C:/Users/xDrais/Desktop/Pdfdetention.pdf");
                             QPainter painter(&pdf);
                            int i = 4000;
                                 painter.setPen(Qt::red);

                                 painter.setFont(QFont("Arial", 30));
                                 painter.drawText(2100,1200,"Liste Des Detentions");
                                 painter.setPen(Qt::green);
                                 painter.setFont(QFont("Arial", 50));
                                 painter.drawRect(1000,200,6500,2000);
                                 painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/xDrais/Desktop/qt/qtprojetc++/projetcCopy/sound/Police.png"));
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

void MainWindow::on_pb_refreshpolicetable_clicked()
{

        player->play();
        ui->tableViewpolice->setModel(police.afficher());

}

void MainWindow::on_pb_missionrefresh_clicked()
{
    player->play();
    ui->tableViewmissions->setModel(mission.afficher());
}
