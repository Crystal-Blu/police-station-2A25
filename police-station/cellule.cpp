#include "cellule.h"
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


Cellules::Cellules()
{
 idcel = 0; nombre_det =0 ; nombre_det_max =0 ; nombre_lit = 0 ;

}


Cellules::Cellules(int idcel ,int nombre_det ,int nombre_det_max,int nombre_lit)
{
    this->idcel=idcel;
    this->nombre_det=nombre_det;
    this->nombre_det_max=nombre_det_max;
    this->nombre_lit=nombre_lit;
}

int Cellules::getidcel()
{
    return idcel ;
}

int Cellules::getnombre_det()
{
    return nombre_det;
}

int Cellules::getnombre_det_max()
{
    return nombre_det_max;
}

int Cellules::getnombre_lit()
{
    return nombre_lit;
}

void Cellules::setidcel(int idcel) {this->idcel=idcel;}
void Cellules::setnombre_det(int nombre_det) {this->nombre_det=nombre_det;}
void Cellules::setnombre_det_max(int nombre_det_max){this->nombre_det_max=nombre_det_max;}
void Cellules::setnombre_lit(int nombre_lit){this->nombre_lit=nombre_lit;}

bool Cellules::ajouter()

{


    QSqlQuery query;
    QString idcel_string = QString::number(idcel);
    QString nombre_det_string = QString::number(nombre_det);
    QString nombre_det_max_string = QString::number(nombre_det_max);
    QString nombre_lit_string = QString::number(nombre_lit);

    query.prepare("INSERT INTO cellules (idcel, nombre_lit, nombre_det, nombre_det_max) "
                  "VALUES (:idcel,:nombre_lit, :nombre_det, :nombre_det_max )");
    query.bindValue(":idcel", idcel_string);
    query.bindValue(":nombre_det", nombre_det_string);
    query.bindValue(":nombre_det_max", nombre_det_max_string);
    query.bindValue(":nombre_lit", nombre_lit_string);


    return query.exec();


}


QSqlQueryModel * Cellules::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM CELLULES");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDCEL"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMBRE_LIT"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRE_DET"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE_DET_MAX"));



    return model;
}


bool Cellules::supprimer(int idcel){
     QSqlQuery query;

     QString idcel_string =   QString::number(idcel);
    query.prepare("delete from cellules where idcel = :idcel");

    query.bindValue(":idcel", idcel_string);


    return query.exec();



}

bool Cellules::modifier(int idcel)


{


    QSqlQuery query;
    QString idcel_string =   QString::number(idcel);
    QString nombre_det_string =   QString::number(nombre_det);
    QString nombre_det_max_string =   QString::number(nombre_det_max);
    QString nombre_lit_string =   QString::number(nombre_lit);

    query.prepare("UPDATE cellules SET nombre_det=:nombre_det, nombre_det_max=:nombre_det_max,nombre_lit=:nombre_lit,idcel=:idcel   WHERE idcel=:idcel" );

    query.bindValue(":idcel", idcel_string);
    query.bindValue(":nombre_det", nombre_det_string);
    query.bindValue(":nombre_det_max", nombre_det_max_string);
    query.bindValue(":nombre_lit", nombre_lit_string);



    return query.exec();



}




void Cellules::ajout_det(int idcel)
{
    QSqlQuery query;
    QString idcel_string =   QString::number(idcel);


    query.prepare("UPDATE cellules SET nombre_det=nombre_det+1  WHERE idcel=:idcel" );

    query.bindValue(":idcel", idcel_string);
    query.exec();


}
