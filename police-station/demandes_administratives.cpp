#include "demandes_administratives.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>



demandes_administratives::demandes_administratives()
{
 iddem = 0; nom =" "; type =" ";DATE_CREATION = QDate::currentDate();idp = 0;cin = 0 ;

}

demandes_administratives::demandes_administratives( int iddem ,int idp ,int cin,QString nom ,QString type ,QDate DATE_CREATION )
{

this->iddem=iddem;
    this->idp=idp;
    this->cin=cin;
    this->nom=nom;
    this->type=type;
    this->DATE_CREATION=DATE_CREATION;
}


int demandes_administratives::getid() {return iddem ;}

int demandes_administratives::getidp() {return idp ;}

int demandes_administratives::getcin() {return cin ;}

QString demandes_administratives::getnom(){return nom;}

QString demandes_administratives::gettype(){return type;}

QDate demandes_administratives::getDATE_CREATION(){return DATE_CREATION;}

 void demandes_administratives::setid(int iddem) {this->iddem=iddem;}

void demandes_administratives::setidp(int idp) {this->idp=idp;}

void demandes_administratives::setcin(int cin) {this->cin=cin;}

void demandes_administratives::setnom(QString nom) {this->nom=nom;}

void demandes_administratives::settype(QString type){this->type=type;}

void demandes_administratives::setDATE_CREATION(QDate DATE_CREATION){this->DATE_CREATION=DATE_CREATION;}

bool demandes_administratives::ajouter_2()


{


    QSqlQuery query;
    QString id_string =   QString::number(iddem);
 QString idp_string =   QString::number(idp);
  QString cin_string =   QString::number(cin);

    query.prepare("INSERT INTO DEMANDES_ADMINISTRATIVES (iddem, nom, type, IDP ,DATE_CREATION,CIN  ) "
                  "VALUES (:iddem, :nom, :type,:IDP,:DATE_CREATION,:CIN )");
    query.bindValue(":iddem", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":DATE_CREATION", DATE_CREATION);
    query.bindValue(":IDP", idp_string);
    query.bindValue(":CIN", cin_string);




    return query.exec();



}
QSqlQueryModel * demandes_administratives::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM DEMANDES_ADMINISTRATIVES");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("iddem"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDP"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_CREATION"));

           model->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN"));





    return model;
}

QSqlQueryModel * demandes_administratives::afficher_combo() {
 QSqlQueryModel * model = new QSqlQueryModel ();


      model->setQuery("SELECT * FROM POLICIER ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDP"));

       return model;
 }


QSqlQueryModel * demandes_administratives::afficher_combo_2() {
 QSqlQueryModel * model = new QSqlQueryModel ();


      model->setQuery("SELECT * FROM CITOYENS ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));

       return model;
 }


bool demandes_administratives::supprimer(int id){
     QSqlQuery query;

     QString id_string =   QString::number(id);
    query.prepare("delete from DEMANDES_ADMINISTRATIVES where iddem = :iddem ");

    query.bindValue(":iddem", id_string);


    return query.exec();



}


bool demandes_administratives::modifier(int iddem)


{


    QSqlQuery query;
    QString iddem_string =   QString::number(iddem);
    QString idp_string =   QString::number(idp);
     QString cin_string =   QString::number(cin);
    query.prepare("UPDATE DEMANDES_ADMINISTRATIVES SET type=:type, nom=:nom,iddem=:iddem,idp=:idp,DATE_CREATION=:DATE_CREATION,cin=:cin   WHERE iddem=:iddem" );

    query.bindValue(":iddem", iddem_string);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":DATE_CREATION", DATE_CREATION);
    query.bindValue(":idp", idp_string);
    query.bindValue(":cin", cin_string);





    return query.exec();



}

