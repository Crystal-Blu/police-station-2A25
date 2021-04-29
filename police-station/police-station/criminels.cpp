#include "criminels.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include <QDate>
Criminels::Criminels()
{

        ID_CRIMINEL=0;
        NOM_CRIMINEL=" ";
        PRENOM_CRIMINEL=" ";
       AGE_CRIMINEL = 0;

}
Criminels::Criminels(int ID_CRIMINEL,int AGE_CRIMINEL,QString NOM_CRIMINEL,QString PRENOM_CRIMINEL)
{
this->ID_CRIMINEL=ID_CRIMINEL;
this->AGE_CRIMINEL=AGE_CRIMINEL;
this->NOM_CRIMINEL=NOM_CRIMINEL;
this->PRENOM_CRIMINEL=PRENOM_CRIMINEL;

}
//Getters
int Criminels::getidc (){return ID_CRIMINEL;}
int  Criminels::getage(){return AGE_CRIMINEL;}
QString  Criminels::getnom() {return NOM_CRIMINEL;}
QString  Criminels::getprenom (){return PRENOM_CRIMINEL;}
//setters

void  Criminels::setidc (int ID_CRIMINEL){this->ID_CRIMINEL=ID_CRIMINEL;}
void  Criminels::setage (int AGE_CRIMINEL){this->AGE_CRIMINEL=AGE_CRIMINEL;}
void  Criminels::setnom (QString NOM_CRIMINEL){this->NOM_CRIMINEL=NOM_CRIMINEL;}
void  Criminels::setprenom (QString PRENOM_CRIMINEL){this->PRENOM_CRIMINEL=PRENOM_CRIMINEL;}
//ajouter_criminel
bool Criminels::ajouter_c()
{
    QSqlQuery query;
    QString res=QString ::number(ID_CRIMINEL);
    query.prepare("INSERT INTO CRIMINELS (ID_CRIMINEL,AGE_CRIMINEL,NOM_CRIMINEL,PRENOM_CRIMINEL)"
            "VALUES(:ID_CRIMINEL,:AGE_CRIMINEL , :NOM_CRIMINEL, :PRENOM_CRIMINEL)");
    query.bindValue(":ID_CRIMINEL",res);
    query.bindValue(":AGE_CRIMINEL",AGE_CRIMINEL);
    query.bindValue(":NOM_CRIMINEL",NOM_CRIMINEL);
    query.bindValue(":PRENOM_CRIMINEL",PRENOM_CRIMINEL);
    return query.exec();
}
//afficher_criminel
QSqlQueryModel * Criminels::afficher_c()


{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM CRIMINELS");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CRIMINEL"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("AGE_CRIMINEL"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM_CRIMINEL"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM_CRIMINEL"));
       return model;
}
bool Criminels::supprimer_c(int ID_CRIMINEL)
{
      QSqlQuery query;
      QString res=QString::number(ID_CRIMINEL);
      query.prepare("DELETE FROM CRIMINELS WHERE ID_CRIMINEL= :ID_CRIMINEL ");
      query.bindValue(":ID_CRIMINEL",res);
      return query.exec();}



bool Criminels::modifier_c(int ID_CRIMINEL)
{


    QSqlQuery query;
    QString res =   QString::number(ID_CRIMINEL);
    query.prepare("UPDATE CRIMINELS SET  AGE_CRIMINEL=:AGE_CRIMINEL,NOM_CRIMINEL=:NOM_CRIMINEL,PRENOM_CRIMINEL=:PRENOM_CRIMINEL,ID_CRIMINEL=:ID_CRIMINEL  WHERE ID_CRIMINEL=:ID_CRIMINEL" );

    query.bindValue(":ID_CRIMINEL", res);
    query.bindValue(":AGE_CRIMINEL", AGE_CRIMINEL);
    query.bindValue(":NOM_CRIMINEL", NOM_CRIMINEL);
    query.bindValue(":PRENOM_CRIMINEL", PRENOM_CRIMINEL);


    return query.exec();



}


/*bool Criminels::Rechercher_c()
{
    QSqlQuery query;
    QString ID_CRIMINELstr=QString::number(ID_CRIMINEL);
    query.prepare("SELECT * from CRIMMINELS(ID_CRIMINEL,  AGE_CRIMINEL, NOM_CRIMINEL, PRENOM_CRIMINEL)");
    return query.exec();
}

*/
