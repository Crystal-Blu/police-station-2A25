#include "missions.h"
#include <QSqlQuery>
#include <QtDebug>

missions::missions()
{
idm=0 ; nom=" "; type=" " ;  idp=0;

}

missions::missions(int idm , QString nom , QString type , QDate date_mission , int idp  )
{
    this->idm=idm ;
    this->nom=nom;
    this->type=type;
    this->date_mission=date_mission ;
    this->idp=idp ;
}

int missions::getidm()
{
    return idm;
}
QString missions::gettype()
{
    return type;
}
QString missions::getnom()
{
    return nom ;
}

QDate missions::getdate_mission()
{
    return date_mission ;
}

int missions::getidp()
{
    return idp;
}




void missions::setidm(int idm)
{
    this->idm=idm;
}
void missions::setnom(QString nom )
{
     this->nom=nom;
}
void missions::settype(QString type )
{
     this->type=type;
}
void missions::setdate_mission(QDate date_mission)
{
    this->date_mission=date_mission;
}
void missions::setidp(int idp)
{
    this->idp=idp;
}


QSqlQueryModel * missions::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from MISSIONS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("idm"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_mission"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("idp"));
    return model;


}

bool missions::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(idm);
    QString resss= QString::number(idp);
    query.prepare("INSERT INTO MISSIONS (idm, nom, type , date_mission ,idp ) "
                  "VALUES (:idm, :nom, :type , :date_mission , :idp )");
    query.bindValue(":idm", res);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":date_mission", date_mission);
    query.bindValue(":idp", resss);


    return query.exec();

}

bool missions::supprimer(int idm)
{
    QSqlQuery query;
    QString res=QString::number(idm);
    query.prepare("Delete from MISSIONS where idm= :idm ");
    query.bindValue(":idm",res);

    return query.exec();
}
