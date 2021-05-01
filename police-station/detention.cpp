#include "detention.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>

detentions::detentions()
{
  iddet= 0 ; raison=" "; idcel= 0 ; idp= 0;
}

detentions::detentions(int iddet ,QDate date_entree, QDate date_sortie, QString raison, int idcel, int idp)
{
    this->iddet=iddet;
    this->date_entree=date_entree;
    this->date_sortie=date_sortie;
    this->raison=raison;
    this->idcel=idcel;
    this->idp=idp;

}

int detentions::getiddet()
{
    return iddet ;
}

QDate detentions::getdate_entree()
{
    return date_entree ;
}

QDate detentions::getdate_sortie()
{
    return date_sortie ;
}


QString detentions::getraison()
{
    return raison;
}

int detentions::getidcel()
{
    return idcel ;
}

int detentions::getidp()
{
    return idp ;
}


void detentions::setiddet(int iddet)
{
    this->iddet=iddet;
}

void detentions::setraison(QString raison)
{
    this->raison=raison;
}

void detentions::setdate_entree(QDate date_entree)
{
    this->date_entree=date_entree;
}

void detentions::setdate_sortie(QDate date_sortie)
{
    this->date_sortie=date_sortie;
}

void detentions::setidcel(int idcel)
{
    this->idcel=idcel;
}

void detentions::setidp(int idp)
{
    this->idp=idp;
}

bool detentions::ajouter()

{
    QSqlQuery query;
    QString iddet_string =   QString::number(iddet);
    QString idcel_string =   QString::number(idcel);
    QString idp_string =   QString::number(idp);

    query.prepare("INSERT INTO detentions (iddet,date_entree,date_sortie,raison,idcel,idp) "
                  "VALUES (:iddet, :date_entree, :date_sortie , :raison, :idcel, :idp)");
    query.bindValue(":iddet", iddet_string);
    query.bindValue(":date_entree", date_entree);
    query.bindValue(":date_sortie", date_sortie);
    query.bindValue(":raison", raison);
    query.bindValue(":idcel", idcel_string);
    query.bindValue(":idp", idp_string);


    return query.exec();



}


QSqlQueryModel * detentions::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel ();


         model->setQuery("SELECT * FROM DETENTIONS");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDDET"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_ENTREE"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_SORTIE"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("RAISON"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDCEL"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("IDP"));


    return model;
}


bool detentions::supprimer(int iddet){
     QSqlQuery query;

     QString iddet_string =   QString::number(iddet);
    query.prepare("delete from detentions where iddet = :iddet ");

    query.bindValue(":iddet", iddet_string);


    return query.exec();

}


bool detentions::modifier(int iddet)


{


    QSqlQuery query;
    QString iddet_string =   QString::number(iddet);
    QString idcel_string =   QString::number(idcel);
    QString idp_string =   QString::number(idp);
    query.prepare("UPDATE detentions SET raison=:raison, date_entree=:date_entree, date_sortie=:date_sortie,iddet=:iddet, idcel=:idcel, idp=:idp  WHERE iddet=:iddet" );

    query.bindValue(":iddet", iddet_string);
    query.bindValue(":date_entree", date_entree);
    query.bindValue(":date_sortie", date_sortie);
    query.bindValue(":raison", raison);
    query.bindValue(":idcel", idcel_string);
    query.bindValue(":idp", idp_string);




    return query.exec();



}
