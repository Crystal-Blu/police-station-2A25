#include "citoyen.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QImage>
#include "mainwindow.h"


Citoyen::Citoyen()
{
 CIN = 0; nom =" "; prenom ="  "; adresse = " ";

}

Citoyen::Citoyen(int CIN ,QString nom ,QString prenom,QString adresse,QByteArray inByteArray,QDate DATE_NAISSANCE,QString path)
{this->CIN=CIN;this->nom=nom;this->prenom=prenom;this->adresse=adresse;this->inByteArray=inByteArray;this->DATE_NAISSANCE =DATE_NAISSANCE;this->path_image=path;}
int Citoyen::getCIN() {return CIN ;}
QString Citoyen::getnom(){return nom;}
QString Citoyen::getprenom(){return prenom;}
QString Citoyen::getadresse(){return adresse;}
QByteArray Citoyen::getphoto(){return inByteArray;}
QDate Citoyen::getdate(){return DATE_NAISSANCE ;}
void Citoyen::setCIN(int CIN) {this->CIN=CIN;}
void Citoyen::setnom(QString nom) {this->nom=nom;}
void Citoyen::setprenom(QString prenom){this->prenom=prenom;}
void Citoyen::setadresse(QString adresse){this->adresse=adresse;}
void Citoyen::setphoto(QByteArray inByteArray){this->inByteArray=inByteArray;}
void Citoyen::setdate(QDate DATE_NAISSANCE){this->DATE_NAISSANCE=DATE_NAISSANCE;}
bool Citoyen::ajouter()


{


    QSqlQuery query;
    QString CIN_string =   QString::number(CIN);


    query.prepare("INSERT INTO CITOYENS (CIN, nom, prenom , adresse, photo ,DATE_NAISSANCE) "
                  "VALUES (:CIN, :nom, :prenom , :adresse, :photo ,:DATE_NAISSANCE)");
    query.bindValue(":CIN", CIN_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":photo", path_image);
    query.bindValue(":DATE_NAISSANCE", DATE_NAISSANCE);
    return query.exec();



}


QSqlQueryModel * Citoyen::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM CITOYENS");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("PHOTO"));



    return model;
}


bool Citoyen::supprimer(int CIN){
     QSqlQuery query;

     QString CIN_string =   QString::number(CIN);
    query.prepare("delete from CITOYENS where CIN = :CIN ");

    query.bindValue(":CIN", CIN_string);


    return query.exec();



}

bool Citoyen::modifier(int CIN)


{


    QSqlQuery query;
    QString CIN_string =   QString::number(CIN);
    query.prepare("UPDATE CITOYENS SET prenom=:prenom, nom=:nom,adresse=:adresse,photo=:photo,DATE_NAISSANCE=:DATE_NAISSANCE,CIN=:CIN   WHERE CIN=:CIN" );

    query.bindValue(":CIN", CIN_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":photo", path_image);
    query.bindValue(":DATE_NAISSANCE", DATE_NAISSANCE);



    return query.exec();



}


