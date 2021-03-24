#include "delits.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include <QDate>
Delits::Delits()
{
    ID_DELIT=0;
    TYPE_DELIT=" ";
    DESCRIPTION_DELIT=" ";
    //date = " ";

}
Delits::Delits(int ID_DELIT,QDate DATE_DELIT,QString TYPE_DELIT,QString DESCRIPTION_DELIT)
{
this->ID_DELIT=ID_DELIT;
this->DATE_DELIT=DATE_DELIT;
this->TYPE_DELIT=TYPE_DELIT;
this->DESCRIPTION_DELIT=DESCRIPTION_DELIT;

}
//Getters
int Delits::getid (){return ID_DELIT;}
QDate  Delits::getdate(){return DATE_DELIT;}
QString  Delits::gettype() {return TYPE_DELIT;}
QString  Delits::getdescription (){return DESCRIPTION_DELIT;}

//setters

void  Delits::settype (QString TYPE_DELIT){this->TYPE_DELIT=TYPE_DELIT;}
void  Delits::setdesciption (QString DESCRIPTION_DELIT){this->DESCRIPTION_DELIT=DESCRIPTION_DELIT;}
void  Delits::setid (int ID_DELIT){this->ID_DELIT=ID_DELIT;}
void  Delits::setdate (QDate DATE_DELIT){this->DATE_DELIT=DATE_DELIT;}







bool Delits::ajouter()
{
    QSqlQuery query;
    QString res=QString ::number(ID_DELIT);
    query.prepare("INSERT INTO DELITS (ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT)"
            "VALUES(:ID_DELIT,:DATE_DELIT , :TYPE_DELIT, :DESCRIPTION_DELIT)");
    query.bindValue(":ID_DELIT",res);
    query.bindValue(":DATE_DELIT",DATE_DELIT);
    query.bindValue(":TYPE_DELIT",TYPE_DELIT);
    query.bindValue(":DESCRIPTION_DELIT",DESCRIPTION_DELIT);
    return query.exec();
}
QSqlQueryModel * Delits::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM DELITS");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_DELIT"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_DELIT"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION_DELIT"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_DELIT"));
       return model;}



bool Delits::supprimer(int ID_DELIT)
{
      QSqlQuery query;
      QString res=QString::number(ID_DELIT);
      query.prepare("DELETE FROM DELITS WHERE ID_DELIT= :ID_DELIT ");
      query.bindValue(":ID_DELIT",res);
      return query.exec();}



bool Delits::modifier(int ID_DELIT)


{


    QSqlQuery query;
    QString res =   QString::number(ID_DELIT);
    query.prepare("UPDATE DELITS SET  DATE_DELIT=:DATE_DELIT,TYPE_DELIT=:TYPE_DELIT,DESCRIPTION_DELIT=:DESCRIPTION_DELIT,ID_DELIT=:ID_DELIT  WHERE ID_DELIT=:ID_DELIT" );

    query.bindValue(":ID_DELIT", res);
    query.bindValue(":DATE_DELIT", DATE_DELIT);
    query.bindValue(":TYPE_DELIT", TYPE_DELIT);
    query.bindValue(":DESCRIPTION_DELIT", DESCRIPTION_DELIT);


    return query.exec();



}


