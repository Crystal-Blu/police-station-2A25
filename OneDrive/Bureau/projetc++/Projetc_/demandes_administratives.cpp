#include "demandes_administratives.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>



demandes_administratives::demandes_administratives()
{
 iddem = 0; nom =" "; type =" ";DATE_CREATION = QDateTime::currentDateTime();

}

demandes_administratives::demandes_administratives( int iddem ,QString nom ,QString type ,QDateTime DATE_CREATION )
{
this->iddem=iddem;this->nom=nom;this->type=type;this->DATE_CREATION=DATE_CREATION;}
int demandes_administratives::getid() {return iddem ;}
QString demandes_administratives::getnom(){return nom;}
QString demandes_administratives::gettype(){return type;}
QDateTime demandes_administratives::getDATE_CREATION(){return DATE_CREATION ;}
void demandes_administratives::setid(int iddem) {this->iddem=iddem;}
void demandes_administratives::setnom(QString nom) {this->nom=nom;}
void demandes_administratives::settype(QString type){this->type=type;}
void demandes_administratives::setDATE_CREATION(QDateTime DATE_CREATION){this->DATE_CREATION=DATE_CREATION;}

bool demandes_administratives::ajouter_2()


{


    QSqlQuery query;
    QString id_string =   QString::number(iddem);
    query.prepare("INSERT INTO DEMANDES_ADMINISTRATIVES (iddem, nom, type,DATE_CREATION ) "
                  "VALUES (:iddem, :nom, :type,:DATE_CREATION  )");
    query.bindValue(":iddem", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":DATE_CREATION", DATE_CREATION);










    return query.exec();



}
QSqlQueryModel * demandes_administratives::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM DEMANDES_ADMINISTRATIVES");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("iddem"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_CREATION"));





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
    query.prepare("UPDATE DEMANDES_ADMINISTRATIVES SET type=:type, nom=:nom,iddem=:iddem,DATE_CREATION=:DATE_CREATION   WHERE iddem=:iddem" );

    query.bindValue(":iddem", iddem_string);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":DATE_CREATION", DATE_CREATION);





    return query.exec();



}
