#include "demandes_administratives.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>



demandes_administratives::demandes_administratives()
{
 id = 0; nom =" "; type =" ";

}

demandes_administratives::demandes_administratives( int id ,QString nom ,QString type    )
{
this->id=id;this->nom=nom;this->type=type;}
int demandes_administratives::getid() {return id ;}
QString demandes_administratives::getnom(){return nom;}
QString demandes_administratives::gettype(){return type;}

void demandes_administratives::setid(int id) {this->id=id;}
void demandes_administratives::setnom(QString nom) {this->nom=nom;}
void demandes_administratives::settype(QString type){this->type=type;}

bool demandes_administratives::ajouter_2()


{


    QSqlQuery query;
    QString id_string =   QString::number(id);
    query.prepare("INSERT INTO demande (id, nom, type ) "
                  "VALUES (:id, :nom, :type  )");
    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);










    return query.exec();



}
QSqlQueryModel * demandes_administratives::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM DEMANDE");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));




    return model;
}


bool demandes_administratives::supprimer(int id){
     QSqlQuery query;

     QString id_string =   QString::number(id);
    query.prepare("delete from demande where id = :id ");

    query.bindValue(":id", id_string);


    return query.exec();



}


bool demandes_administratives::modifier(int id)


{


    QSqlQuery query;
    QString id_string =   QString::number(id);
    query.prepare("UPDATE demande SET type=:type, nom=:nom,id=:id   WHERE id=:id" );

    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);




    return query.exec();



}
