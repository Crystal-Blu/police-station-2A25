#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "vehicule_modifier_window.h"

QString Affichagevehicule_Query="select * from vehicules",groupebyvehi="",Affichagevehicule_Query_f=Affichagevehicule_Query+groupebyvehi;
QString AffichageEq_Query="select * from equipements",groupbyeq="",Affichageeq_Query_f=AffichageEq_Query+groupbyeq;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
    ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
    ui->tableView_4->setModel(R.Afficher_rep());

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);

}

void MainWindow::on_ajouter_clicked()
{
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
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout Effectué avec succées \n"), QMessageBox::Ok);
    }
    if (!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),QObject::tr("Ajout Non Effectué \n"), QMessageBox::Ok);
    }

}

void MainWindow::on_Refresh_clicked()
{
    ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
}

int MainWindow::on_Vehicule_table_activated(const QModelIndex &index)
{
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
    int matricule=ui->matslected->text().toInt();
    V.delete_vehicule(matricule);
     ui->Vehicule_table->setModel(V.afficher_vehicules(Affichagevehicule_Query_f));
}

void MainWindow::on_Modif_btton_clicked()
{
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
    bool test;
    int id=ui->lineEdit_7->text().toInt();
    int matricule=ui->Matricule_eq_edit->text().toInt();
    QString type_eq=ui->type_edit->text();
    Equipements EQ(id,matricule,type_eq);
    test=EQ.ajouter_Equipements();
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

void MainWindow::on_pushButton_13_clicked()
{
    ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
}

int MainWindow::on_Equipemen_table_activated(const QModelIndex &index)
{
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
    int id=ui->lineEdit_6->text().toInt();
    E.delete_Equipments(id);
     ui->Equipemen_table->setModel(E.afficher_equipments(Affichageeq_Query_f));
}


void MainWindow::on_pushButton_10_clicked()
{
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
    ui->tableView_4->setModel(R.Afficher_rep());
}

void MainWindow::on_tableView_4_activated(const QModelIndex &index)
{
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
    ui->tabWidget->setCurrentWidget(ui->tab_6);
    ui->tabWidget_4->setCurrentWidget(ui->tab_19);
    QString mat=ui->matslected->text();
    ui->MatriculeEdit_2->setText(mat);
}

void MainWindow::on_ajouter_2_clicked()
{
    bool test;
    int mat=ui->MatriculeEdit_2->text().toInt();
    int id=ui->idreparation->text().toInt();
    QString type=ui->nikrabek->text();
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
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout Effectué avec succées \n"), QMessageBox::Ok);
    }
    if (!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),QObject::tr("Ajout Non Effectué \n"), QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_18_clicked()
{
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
    ui->lineEdit_3->clear();
    Affichagevehicule_Query_f="select * from vehicules ";
}

void MainWindow::on_radioButton_15_clicked()
{
   if(ui->lineEdit_3->text()=="")
    Affichagevehicule_Query="select * from vehicules ";

    updateaffichagevehicule();
}


void MainWindow::on_radioButton_18_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_17_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_16_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_13_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_14_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_21_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_22_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_9_clicked()
{
    if(ui->lineEdit_3->text()=="")
     Affichagevehicule_Query="select * from vehicules ";

     updateaffichagevehicule();
}

void MainWindow::on_radioButton_7_clicked()
{
    if(ui->lineEdit_2->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_10_clicked()
{
    if(ui->lineEdit_2->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_8_clicked()
{
    if(ui->lineEdit_2->text()=="")
     AffichageEq_Query="select * from Equipements ";

     updateaffichageeq();
}

void MainWindow::on_radioButton_11_clicked()
{
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
