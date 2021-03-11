#include "citoyen.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>

Citoyen::Citoyen()
{
 CIN = 0; nom =" "; prenom ="  "; adresse = " " ;

}

Citoyen::Citoyen(int CIN ,QString nom ,QString prenom,QString adresse,QDate date)
{this->CIN=CIN;this->nom=nom;this->prenom=prenom;this->adresse=adresse;this->date=date; }
int Citoyen::getCIN() {return CIN ;}
QString Citoyen::getnom(){return nom;}
QString Citoyen::getprenom(){return prenom;}
QString Citoyen::getadresse(){return adresse;}
QDate Citoyen::getdate(){return date ;}
void Citoyen::setCIN(int CIN) {this->CIN=CIN;}
void Citoyen::setnom(QString nom) {this->nom=nom;}
void Citoyen::setprenom(QString prenom){this->prenom=prenom;}
void Citoyen::setadresse(QString adresse){this->prenom=adresse;}
void Citoyen::setdate(QDate date){this->date=date;}
bool Citoyen::ajouter()


{


    QSqlQuery query;
    QString CIN_string =   QString::number(CIN);

    query.prepare("INSERT INTO citoyen (CIN, nom, prenom , adresse) "
                  "VALUES (:CIN, :nom, :prenom , :adresse)");
    query.bindValue(":CIN", CIN_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);









    return query.exec();



}


QSqlQueryModel * Citoyen::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM CITOYEN");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));



    return model;
}


bool Citoyen::supprimer(int CIN){
     QSqlQuery query;

     QString CIN_string =   QString::number(CIN);
    query.prepare("delete from citoyen where CIN = :CIN ");

    query.bindValue(":CIN", CIN_string);


    return query.exec();



}

bool Citoyen::modifier(int CIN)


{


    QSqlQuery query;
    QString CIN_string =   QString::number(CIN);
    query.prepare("UPDATE citoyen SET prenom=:prenom, nom=:nom,adresse=:adresse,CIN=:CIN   WHERE CIN=:CIN" );

    query.bindValue(":CIN", CIN_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);



    return query.exec();



}


