#include "cellule.h"
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


Cellule::Cellule()
{
 id = 0; nbre_det =0 ; nbre_det_max =0 ; nbre_lit = 0 ;

}


Cellule::Cellule(int id ,int nbre_det ,int nbre_det_max,int nbre_lit)
{
    this->id=id;
    this->nbre_det=nbre_det;
    this->nbre_det_max=nbre_det_max;
    this->nbre_lit=nbre_lit;
}

int Cellule::getid()
{
    return id ;
}

int Cellule::getnbre_det()
{
    return nbre_det;
}

int Cellule::getnbre_det_max()
{
    return nbre_det_max;
}

int Cellule::getnbre_lit()
{
    return nbre_lit;
}

void Cellule::setid(int id) {this->id=id;}
void Cellule::setnbre_det(int nbre_det) {this->nbre_det=nbre_det;}
void Cellule::setnbre_det_max(int nbre_det_max){this->nbre_det_max=nbre_det_max;}
void Cellule::setnbre_lit(int nbre_lit){this->nbre_lit=nbre_lit;}

bool Cellule::ajouter()

{


    QSqlQuery query;
    QString id_string =   QString::number(id);
    QString nbre_det_string =   QString::number(nbre_det);
    QString nbre_det_max_string =   QString::number(nbre_det_max);
    QString nbre_lit_string =   QString::number(nbre_lit);

    query.prepare("INSERT INTO cellule (id, nbre_det, nbre_det_max , nbre_lit) "
                  "VALUES (:id, :nbre_det, :nbre_det_max , :nbre_lit)");
    query.bindValue(":id", id_string);
    query.bindValue(":nbre_det", nbre_det_string);
    query.bindValue(":nbre_det_max", nbre_det_max_string);
    query.bindValue(":nbre_lit", nbre_lit_string);


    return query.exec();


}


QSqlQueryModel * Cellule::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM CELLULE");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NBRE_DET"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBRE_DET_MAX"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("NBRE_LIT"));


    return model;
}


bool Cellule::supprimer(int id){
     QSqlQuery query;

     QString id_string =   QString::number(id);
    query.prepare("delete from cellule where id = :id ");

    query.bindValue(":id", id_string);


    return query.exec();



}

bool Cellule::modifier(int id)


{


    QSqlQuery query;
    QString id_string =   QString::number(id);
    QString nbre_det_string =   QString::number(nbre_det);
    QString nbre_det_max_string =   QString::number(nbre_det_max);
    QString nbre_lit_string =   QString::number(nbre_lit);

    query.prepare("UPDATE cellule SET nbre_det=:nbre_det, nbre_det_max=:nbre_det_max,nbre_lit=:nbre_lit,id=:id   WHERE id=:id" );

    query.bindValue(":id", id_string);
    query.bindValue(":nbre_det", nbre_det_string);
    query.bindValue(":nbre_det_max", nbre_det_max_string);
    query.bindValue(":nbre_lit", nbre_lit_string);



    return query.exec();



}

