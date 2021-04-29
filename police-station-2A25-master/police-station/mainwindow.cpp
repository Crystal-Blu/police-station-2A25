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
#include <QFileDialog>
#include "arduino.h"
#include "cellule.h"
#include "detention.h"
#include"delits.h"
#include "chart.h"
#include "criminels.h"
#include<QMediaPlayer>
#include<QSoundEffect>
#include"charttype.h"
#include<QIntValidator>
#include <QValidator>
#include<QQuickItem>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include "excel.h"
#include <QDialog>

<<<<<<< HEAD:police-station-2A25-master/police-station/mainwindow.cpp
#include "Calculer.h"





=======
>>>>>>> 4b72cd115d2f70b07d201ec32f156c78485c7144:police-station/mainwindow.cpp
QString Affichagevehicule_Query="select * from vehicules",groupebyvehi="",Affichagevehicule_Query_f=Affichagevehicule_Query+groupebyvehi;
QString AffichageEq_Query="select * from equipements",groupbyeq="",Affichageeq_Query_f=AffichageEq_Query+groupbyeq;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
   ui->quickWidget->show();

    init_history_count();
   mModel= new QStandardItemModel(this); //excel
   ui->tableViewExcel->setModel(mModel);  //excel


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
        connect(timer, SIGNAL(timeout()), this, SLOT(check_history()));
        timer->start(1000);

    remplir_equipements();
    remplir_vehi();
    mySystemTrayIcon = new QSystemTrayIcon(this);
    mySystemTrayIcon->setIcon(QIcon(":/new/prefix1/Police.png"));
    mySystemTrayIcon->setVisible(true);
    player->setMedia(QUrl("qrc:/new/prefix1/click.wav"));
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
    ui->tableHistory->setModel(get_history());
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
    //controle de saisie cellule+detention
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



    ui->le_cin->setValidator ( new QIntValidator(0, 99999999, this));

    ui->le_supp->setValidator ( new QIntValidator(0, 99999999, this));
    ui->le_supp_2->setValidator ( new QIntValidator(0, 999999, this));
    ui->le_id->setValidator ( new QIntValidator(0, 999999, this));
     ui->le_id_2->setValidator ( new QIntValidator(0, 999999, this));
      ui->le_cin_modif->setValidator ( new QIntValidator(0, 99999999, this));

    ui->tab_citoyen->setModel(Ci.afficher());
     ui->comboBox->setModel(d.afficher_combo());
      ui->comboBox_cin->setModel(d.afficher_combo_2());
    ui->tab_citoyen_modifier->setModel(Ci.afficher());
    ui->tab_citoyen_2->setModel(Ci.afficher());
    ui->tab_demande->setModel(d.afficher());
     ui->tab_demande_2->setModel(d.afficher());
      ui->tableView->setModel(d.afficher());


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



    //CONTROLE SAISIE ID CRIMINEL

    QRegExp rx("[0-9]{5}");


    QValidator *validator = new QRegExpValidator(rx, this);

    ui->lineEdit_id_c->setValidator(validator);
    ui->lineEdit_ID_cm->setValidator(validator);
    ui->lineEdit_supp_c->setValidator(validator);
    ui->lineEdit_recherche_c->setValidator(validator);




    //CONTROLE SAISIE ID DELIT


    QRegExp rx1("[0-9]{4}");
    QValidator *validator1 = new QRegExpValidator(rx, this);
    ui->lineEdit_rechercher_d->setValidator(validator1);
    ui->lineEdit_supprimer_d->setValidator(validator1);
    ui->le_mid->setValidator(validator1);
    ui->ledelitid->setValidator(validator1);


//INITIATION AFFICHAGE



    //AFFICHAGE NOMBRE CRIMINEL

    QSqlQuery query;
       int numRows= 0;
       query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
       if(query.first())
           numRows = query.value(0).toInt();
       QString numRowsstr=QString::number(numRows);

ui->lineEdit_nombre_criminel->setText(numRowsstr);

//INITIATION MEDIAPLAYER


mMediaPlayer = new QMediaPlayer (this);
connect(mMediaPlayer,&QMediaPlayer ::positionChanged,[&](qint64 pos){
    ui->avance->setValue(pos);
}    );
connect(mMediaPlayer,&QMediaPlayer::durationChanged,[&](qint64 dur) {
    ui->avance->setMaximum(dur);
});


mmMediaPlayer = new QMediaPlayer (this);


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
    QFile f(":/new/prefix1/themes/Darkeum.qss");

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
    QFile f(":/qdarkstyle/light/style.qss");
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
    QFile f(":/darkorange.qss");

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
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/Pdfvehicules.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);
                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Vehicules");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap(":/new/prefix1/vehicules.jpg"));
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
                                             QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pdfvehicules.pdf"));
                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();
    }
}

void MainWindow::on_print_pdf_equipements_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/Pdfequipements.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);
                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Equipements");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap(":/new/prefix1/vehicules.jpg"));
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
                                             QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pdfequipements.pdf"));
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
{    player->play();

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



    player->play();
int idp = ui->le_policeid->text().toInt();
QString rfid=ui->rfid_line->text();
QString nom=ui->le_nompolice->text();
QString prenom=ui->le_prenompolice->text();
QString grade=ui->le_grade->text();
int idpchef = ui->le_chefid->text().toInt();

policier p(idp,nom,prenom,grade,idpchef);
p.setrfid(rfid);
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
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/Pdfmissions.pdf");
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
                                         QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pdfmissions.pdf"));

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



void MainWindow::on_pushButton_maya_1_clicked()
{
    player->play();
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-3);

}


void MainWindow::on_pushButton_ajouter_cel_clicked()
{
    player->play();
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

    player->play();
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
    player->play();
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
    player->play();
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
    player->play();
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
    player->play();
    int iddet  = ui->id_det_supp->text().toInt();
        bool test = De1.supprimer(iddet);

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
      player->play();
      QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                  "/home",
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);
      qDebug()<<dir;
      QPdfWriter pdf(dir+"/Pdfdetention.pdf");
                             QPainter painter(&pdf);
                            int i = 4000;
                                 painter.setPen(Qt::red);

                                 painter.setFont(QFont("Arial", 30));
                                 painter.drawText(2100,1200,"Liste Des Detentions");
                                 painter.setPen(Qt::black);
                                 painter.setFont(QFont("Arial", 50));
                                 painter.drawRect(1000,200,6500,2000);
                                 painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap(":/new/prefix1/detention.jpg"));
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
                                         QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pdfdetention.pdf"));

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

void MainWindow::on_pushButton_maya_2_clicked()
{
    player->play();
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-2);
}



void MainWindow::on_pushButton_maya_3_clicked()
{
    player->play();
    ui->tabcellule->setCurrentIndex(ui->tabcellule->count()-1);
}



void MainWindow::on_pushButton_maya_4_clicked()
{
    player->play();
    ui->tabWidget_detention->setCurrentWidget(ui->tab_29);
}



void MainWindow::on_pushButton_maya_5_clicked()
{
    player->play();
    ui->tabWidget_detention->setCurrentWidget(ui->tab_30);
}



void MainWindow::on_pushButton_maya_6_clicked()
{
    player->play();
    ui->tabWidget_detention->setCurrentWidget(ui->tab_31);
}


void MainWindow::on_pushButton_lumiere_act_clicked() //activer systeme lumière
{
    player->play();
    A.write_to_arduino("1");
}



void MainWindow::on_pushButton_lumiere_desact_clicked() //desactiver systeme lumière
{
   player->play();
    A.write_to_arduino("0");
}

void MainWindow::update_label_lumiere()
{
    /* data=A.read_from_arduino();
    if (data=="1")
        ui->label_etat_lumiere->setText("lumières allumées");
    else if (data=="0" || data=="2")
    ui->label_etat_lumiere->setText("lumières eteinte"); */
};


void MainWindow::on_rafraichir_maya1_clicked()
{
    player->play();
    ui->tableView_cellule->setModel(C.afficher());

}

void MainWindow::on_rafraichir_maya2_clicked()
{
    player->play();
    ui->tableView_detention->setModel(D.afficher());
}

void MainWindow::on_pushButton_modifiercriminel_2_clicked()
{
    int ID_DELIT=ui->ledelitid->text().toInt();
    QString TYPE_DELIT=ui->comboBox_type_d2->currentText();


    QString DESCRIPTION_DELIT=ui->le_desc_delit->text();
    QDate DATE_DELIT=ui->dateEditdelit->date();
    int ID_CRIMINEL=ui->comboBox_id_c->currentText().toInt();
    Delits H(ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT,ID_CRIMINEL);
    bool test=H.ajouter();
    if (test){

        ui->tab_delit1->setModel(De1.afficher());
        ui->tab_delit2->setModel(De1.afficher());


            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_PB_load_clicked()
{
     player->play();
    QSqlQuery query;
    query.exec("SELECT ID_CRIMINEL FROM CRIMINELS");
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    ui->comboBox_id_c->setModel(model);
        qDebug() <<(model->rowCount());
}

void MainWindow::on_pushButton_trierdelitdate_clicked()
{

        player->play();




    QSqlQuery query;
    query.exec("SELECT * FROM DELITS ORDER BY DATE_DELIT");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    QTableView *view =ui->tab_delit1;

       view->setModel(model);
       ui->lineEdit_ID_cm->setText("");
}

void MainWindow::on_pushButton_trierdelittype_clicked()
{
     player->play();

    QSqlQuery query;
    query.exec("SELECT * FROM DELITS ORDER BY TYPE_DELIT");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    QTableView *view =ui->tab_delit1;

       view->setModel(model);
       ui->lineEdit_ID_cm->setText("");

}

void MainWindow::on_pushButton_chart2_clicked()
{    player->play();

     charttype charttype;
      charttype.setModal(true);
      charttype.exec();
}

void MainWindow::on_pushButton_supprimerdelit_clicked()
{
    int ID_DELIT=ui->lineEdit_supprimer_d->text().toInt();
    bool test =De1.supprimer(ID_DELIT);

    if (test){

     ui->tab_delit1->setModel(De1.afficher());
     ui->tab_delit2->setModel(De1.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
 QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modifierdelit_clicked()
{
    int ID_DELIT=ui->le_mid->text().toInt();
    QString TYPE_DELIT=ui->comboBox_type_d->currentText();
    QString DESCRIPTION_DELIT=ui->lineEdit_desc_d->text();
     QDate DATE_DELIT=ui->dateEdit_3->date();
     int ID_CRIMINEL=ui->comboBox_id_c->currentText().toInt();

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

void MainWindow::on_pushButton_rechercherdelit_clicked()
{
     player->play();

    QSqlQuery query;
    int ID_DELIT=ui->lineEdit_rechercher_d->text().toInt();

    QString ID_DELITstr=QString::number(ID_DELIT);

    query.exec("SELECT * from DELITS WHERE ID_DELIT  ='"+ID_DELITstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tab_delit2;

        view->setModel(model);
        ui->lineEdit_rechercher_d->setText("");
}

void MainWindow::on_pushButton_ajoutcriminel_clicked()
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

    ui->lineEdit_nombre_criminel->setText(numRowsstr);
        ui->tab_criminel1->setModel(C1.afficher_c());

        ui->tab_criminel2->setModel(C1.afficher_c());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supp_cri_clicked()
{

    int ID_CRIMINEL=ui->lineEdit_supp_c->text().toInt();
    bool test =Cr1.supprimer_c(ID_CRIMINEL);

    if (test){
        QSqlQuery query;
           int numRows= 0;
           query.exec("SELECT COUNT(*) FROM CRIMINELS  ");
           if(query.first())
               numRows = query.value(0).toInt();
           QString numRowsstr=QString::number(numRows);

    ui->lineEdit_nombre_criminel->setText(numRowsstr);
     ui->tab_criminel1->setModel(Cr1.afficher_c());
     ui->tab_criminel2->setModel(Cr1.afficher_c());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Suppression effectué\n"
    "Click Cancel to exit"),QMessageBox::Cancel);


        }
        else
 QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modifiercriminel_clicked()
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

void MainWindow::on_pushButton_recherchercriminel_clicked()
{
        player->play();

    QSqlQuery query;
    int ID_CRIMINEL=ui->lineEdit_recherche_c->text().toInt();

    QString ID_CRIMINELstr=QString::number(ID_CRIMINEL);

    query.exec("SELECT * from CRIMINELS WHERE ID_CRIMINEL  ='"+ID_CRIMINELstr+"'   ");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

     QTableView *view =ui->tab_criminel2;

        view->setModel(model);
        ui->lineEdit_ID_cm->setText("");
}

void MainWindow::on_pushButton_chart1_clicked()
{
    player->play();
    chart chart;
    chart.setModal(true);
    chart.exec();
}

void MainWindow::on_pushButton_exprterpdfcri_clicked()
{

       player->play();

       QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                   "/home",
                                                   QFileDialog::ShowDirsOnly
                                                   | QFileDialog::DontResolveSymlinks);
       qDebug()<<dir;
       QPdfWriter pdf(dir+"/PdfCriminel.pdf");                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);

                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Criminel");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap(":/homme.jpg"));
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
                                             QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfCriminel.pdf"));

                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();





}
}

void MainWindow::on_pushButton_ouvm_clicked()
{
        player->play();
   QString filename = QFileDialog :: getOpenFileName(this,"police");
   if (filename.isEmpty()) {return;}
   mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
   mMediaPlayer->setVolume(ui->volume->value());
   on_pushButton_play_clicked();
}

void MainWindow::on_pushButton_play_clicked()
{
      player->play();
    mMediaPlayer->play();
}

void MainWindow::on_pushButton_pause_clicked()
{
    QUrl url ;
  url = QUrl("C:/Users/Ilyes/Downloads/button.wav");

        player->play();
    mMediaPlayer->pause();
}

void MainWindow::on_pushButton_stop_clicked()
{
     player->play();;
    mMediaPlayer->stop();
}

void MainWindow::on_pushButton_mute_clicked()
{
      player->play();
    if(ui->pushButton_mute->text()=="MUTE"){
    mMediaPlayer->setMuted(true);
    ui->pushButton_mute->setText("UNMUTE");
   }else {
       mMediaPlayer->setMuted(false);
       ui->pushButton_mute->setText("MUTE");
}}

void MainWindow::on_volume_valueChanged(int value)
{
    mMediaPlayer->setVolume(value);
}

void MainWindow::on_pushButton_ilyesrefresh_clicked()
{     player->play();
   ui->tab_delit1->setModel(De1.afficher());
ui->tab_delit2->setModel(De1.afficher());



}

void MainWindow::on_pushButton_ilyes_cri_clicked()
{
         player->play();
    ui->tab_criminel1->setModel(Cr1.afficher_c());
    ui->tab_criminel2->setModel(Cr1.afficher_c());

}


void MainWindow::on_pushButton_2_clicked()
{

       player->play();
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images Files (*.png *.jpg *.jpeg *.bmp)"));
    Ci.set_path(filename);
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
    player->play();

    int CIN=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->lineEdit_16->text();
    QString adresse=ui->le_adresse->text();
  QByteArray inByteArray /* = ui->label_21->pixmap()-> */;

   QDate DATE_NAISSANCE=ui->dateEdit->date() ;
    QString path=Ci.get_path();
    Citoyen Ci(CIN,nom,prenom,adresse,inByteArray,DATE_NAISSANCE,path);
    bool test = Ci.ajouter();

    if (test){

        ui->comboBox->setModel(d.afficher_combo());
         ui->comboBox_cin->setModel(d.afficher_combo_2());
ui->tab_citoyen_modifier->setModel(Ci.afficher());
 ui->tab_citoyen->setModel(Ci.afficher());
 ui->tab_citoyen_2->setModel(Ci.afficher());
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

    player->play();


    int CIN  = ui->le_supp->text().toInt();
    bool test = c1.supprimer(CIN);

    if (test){
        ui->comboBox->setModel(d.afficher_combo());
         ui->comboBox_cin->setModel(d.afficher_combo_2());

ui->tab_citoyen_modifier->setModel(Ci.afficher());
 ui->tab_citoyen->setModel(Ci.afficher());
 ui->tab_citoyen_2->setModel(Ci.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectué\n"
"Click Cancel to exit"),QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression  non effectué.\n" "Clic Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_update_button_clicked()
{
    player->play();

        int CIN=ui->le_cin_modif->text().toInt();
        QString nom=ui->le_nom_modif->text();
        QString prenom=ui->le_prenom_modif->text();
        QString adresse=ui->le_adresse_modif->text();
        QString path=Ci.get_path();
     QByteArray inByteArray/* =ui->label_21->setPixmap */;
         QDate DATE_NAISSANCE=ui->dateN_modif->date();
        Citoyen Ci(CIN,nom,prenom,adresse,inByteArray,DATE_NAISSANCE,path);
        bool test = Ci.modifier(CIN);

        if (test){
            ui->comboBox->setModel(d.afficher_combo());
             ui->comboBox_cin->setModel(d.afficher_combo_2());
    ui->tab_citoyen_modifier->setModel(Ci.afficher());
     ui->tab_citoyen->setModel(Ci.afficher());
     ui->tab_citoyen_2->setModel(Ci.afficher());

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

    player->play();
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
    player->play();

    int id = ui->le_supp_2->text().toInt();

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

    player->play();

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

    player->play();

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/Pdfvehicules.pdf");
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
                                             QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pdfvehicules.pdf"));

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
    Ci.set_path(filename);
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

void MainWindow::on_refresh_citoyen_clicked()
{
    player->play();
    ui->tab_citoyen->setModel(Ci.afficher());
     ui->comboBox->setModel(d.afficher_combo());
      ui->comboBox_cin->setModel(d.afficher_combo_2());
    ui->tab_citoyen_modifier->setModel(Ci.afficher());
    ui->tab_citoyen_2->setModel(Ci.afficher());
    ui->tab_demande->setModel(d.afficher());
     ui->tab_demande_2->setModel(d.afficher());
      ui->tableView->setModel(d.afficher());
}

void MainWindow::on_Refresh_demande_clicked()
{
    player->play();

    ui->tab_citoyen->setModel(C.afficher());
     ui->comboBox->setModel(d.afficher_combo());
      ui->comboBox_cin->setModel(d.afficher_combo_2());
    ui->tab_citoyen_modifier->setModel(C.afficher());
    ui->tab_citoyen_2->setModel(C.afficher());
    ui->tab_demande->setModel(d.afficher());
     ui->tab_demande_2->setModel(d.afficher());
      ui->tableView->setModel(d.afficher());
}

void MainWindow::on_refreshmap_clicked()
{
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
   ui->quickWidget->show();
}



void MainWindow::on_ouvrir_excel_clicked()
{
  auto filename = QFileDialog::getOpenFileName(this,"ouvrir",QDir::rootPath(),"CSV File(*.csv)");
 if (filename.isEmpty()) {
     return;
 }
 QFile file(filename);
 if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
 {
     return;
 }
 QTextStream xin(&file);
 int lign= 0;
 while(!xin.atEnd())
 {
     mModel->setRowCount(lign);
     auto line = xin.readLine();
     auto values = line.split(";");
     const int col=values.size();
     mModel->setColumnCount(col);
     for(int i=0; i<col; i++)
    {
     setValueAt(lign,i,values.at(i));


     }

          ++lign;
 }
 file.close();
}

void MainWindow::on_nouveau_excel_clicked()
{
    excel d(this);
    if ( d.exec() == QDialog::Rejected)
    {
     return;
    }
    const int col=d.getcol();
    const int lign=d.getlign();
    mModel->setRowCount(lign);
    mModel->setColumnCount(col);
}

void MainWindow::on_enregistrer_sous_excel_clicked()
{
  auto filename= QFileDialog::getSaveFileName(this,"enregister",QDir::rootPath(),"CSV File (*.csv)");
if (filename.isEmpty())
{
 return;
}
QFile file(filename);
if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
{
    return ;
}
QTextStream xout(&file);
const int lign = mModel->rowCount();
const int col = mModel->columnCount();

for ( int i=0 ; i<lign; ++i)
{   xout <<getValueAt(i,0);
    for (int j=1; j<col ; ++j )
    {
     xout<< " ; " << getValueAt(i,j);
    }
    xout <<"\n";
}

file.flush();
file.close();

}


void MainWindow::setValueAt(int ix, int jx, const QString &value)
{
  if (!mModel->item(ix,jx))
  {
      mModel->setItem(ix,jx,new QStandardItem(value));
  }
  else {
      mModel->item(ix,jx)->setText(value);
  }
}


QString MainWindow::getValueAt(int ix, int jx)
{
    if (!mModel->item(ix,jx))
    {
        return "";
    }
    return mModel->item(ix,jx)->text();
}

void MainWindow::check_history()
{
    QString A="";
    int C=0;
    QSqlQuery query;
    query.prepare("select count(*) from historique");
    query.exec();
    while(query.next())
    {
        C=query.value(0).toInt();
    }
    query.prepare("SELECT *FROM (SELECT * FROM historique order by date_m desc)WHERE ROWNUM <= 1;");
    query.exec();
    while(query.next())
    {
        if(query.value(2).toString()=="A")
        {
            A="Un Nouvel élèment a été ajouté de la table ";
        }
        else if(query.value(2).toString()=="U")
        {
            A="Un élèment a été Modifié de la table ";
        }
        else if(query.value(2).toString()=="D")
        {
            A="Un élèment a été supprimé de la table ";
        }
        A=A+query.value(1).toString();
    }
    if (C!=counthistory)
    {
        mySystemTrayIcon->showMessage(tr("Alerte"),tr(A.toStdString().c_str()));
        counthistory=C;
    }

}

QSqlQueryModel * MainWindow::get_history()
{
            QSqlQueryModel * modele=new QSqlQueryModel();
            modele->setQuery("select * from historique order by date_m desc");
            modele->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modele->setHeaderData(1,Qt::Horizontal,QObject::tr("Table"));
            modele->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
            /*modele->setHeaderData(3,Qt::Horizontal,QObject::tr("Description"));*/
            modele->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
            return modele;
}
void MainWindow::on_refreshhistory_clicked()
{
     ui->tableHistory->setModel(get_history());
}
void MainWindow::init_history_count()
{
    QSqlQuery query;
    query.prepare("select count(*) from historique");
    query.exec();
    while(query.next())
    {
       counthistory=query.value(0).toInt();
    }
}
<<<<<<< HEAD:police-station-2A25-master/police-station/mainwindow.cpp

void MainWindow::on_pb_calculatorwindow_clicked()
{



     calc.show();

}
=======
>>>>>>> 4b72cd115d2f70b07d201ec32f156c78485c7144:police-station/mainwindow.cpp
