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
    ID_CRIMINEL=0;

}
Delits::Delits(int ID_DELIT,QDate DATE_DELIT,QString TYPE_DELIT,QString DESCRIPTION_DELIT,int ID_CRIMINEL)
{
this->ID_DELIT=ID_DELIT;
this->DATE_DELIT=DATE_DELIT;
this->TYPE_DELIT=TYPE_DELIT;
this->DESCRIPTION_DELIT=DESCRIPTION_DELIT;
this->ID_CRIMINEL=ID_CRIMINEL;
}
//Getters
int Delits::getid (){return ID_DELIT;}
int Delits::getidc (){return ID_CRIMINEL;}

QDate  Delits::getdate(){return DATE_DELIT;}
QString  Delits::gettype() {return TYPE_DELIT;}
QString  Delits::getdescription (){return DESCRIPTION_DELIT;}

//setters

void  Delits::settype (QString TYPE_DELIT){this->TYPE_DELIT=TYPE_DELIT;}
void  Delits::setdesciption (QString DESCRIPTION_DELIT){this->DESCRIPTION_DELIT=DESCRIPTION_DELIT;}
void  Delits::setid (int ID_DELIT){this->ID_DELIT=ID_DELIT;}
void  Delits::setdate (QDate DATE_DELIT){this->DATE_DELIT=DATE_DELIT;}
void  Delits::setidc (int ID_CRIMINEL){this->ID_CRIMINEL=ID_CRIMINEL;}




bool Delits::ajouter()
{
    QSqlQuery query;
    QString res=QString ::number(ID_DELIT);
    QString res1=QString ::number(ID_CRIMINEL);

    query.prepare("INSERT INTO DELITS (ID_DELIT,DATE_DELIT,TYPE_DELIT,DESCRIPTION_DELIT,ID_CRIMINEL)"
            "VALUES(:ID_DELIT,:DATE_DELIT , :TYPE_DELIT, :DESCRIPTION_DELIT , :ID_CRIMINEL)");
    query.bindValue(":ID_DELIT",res);
    query.bindValue(":DATE_DELIT",DATE_DELIT);
    query.bindValue(":TYPE_DELIT",TYPE_DELIT);
    query.bindValue(":DESCRIPTION_DELIT",DESCRIPTION_DELIT);
    query.bindValue(":ID_CRIMINEL",res1);

    return query.exec();
}
QSqlQueryModel * Delits::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM DELITS");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_DELIT"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_DELIT"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE_DELIT"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION_DELIT"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_CRIMINEL"));

       return model;}



bool Delits::supprimer(int ID_DELIT)
{
      QSqlQuery query;
      QString res=QString::number(ID_DELIT);
      query.prepare("DELETE FROM DELITS WHERE ID_DELIT= :ID_DELIT ");
      query.bindValue(":ID_DELIT",res);
      return query.exec();}



bool Delits::modifier(int ID_DELIT) {
    QSqlQuery query;
    QString res =   QString::number(ID_DELIT);
    QString res1=QString ::number(ID_CRIMINEL);

    query.prepare("UPDATE DELITS SET  DATE_DELIT=:DATE_DELIT,TYPE_DELIT=:TYPE_DELIT,DESCRIPTION_DELIT=:DESCRIPTION_DELIT,ID_DELIT=:ID_DELIT,ID_CRIMINEL=:ID_CRIMINEL  WHERE ID_DELIT=:ID_DELIT" );

    query.bindValue(":ID_DELIT", res);
    query.bindValue(":DATE_DELIT", DATE_DELIT);
    query.bindValue(":TYPE_DELIT", TYPE_DELIT);
    query.bindValue(":DESCRIPTION_DELIT", DESCRIPTION_DELIT);
    query.bindValue(":ID_CRIMINEL", res1);


    return query.exec();



}

QSqlQueryModel * Delits::trier()
{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM DELITS ORDER BY TYPE_DELIT ");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_DELIT"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_DELIT"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION_DELIT"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_DELIT"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_CRIMINEL"));

       return model;}

