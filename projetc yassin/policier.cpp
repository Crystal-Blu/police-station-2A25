#include "policier.h"
 #include <QSqlQuery>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

policier::policier()
{
idp=0 ; nom=" "; prenom=" " ;  grade=" " ; idpchef=0 ;

}

policier::policier(int idp , QString nom , QString prenom , QString grade , int idpchef  )
{
    this->idp=idp ;
    this->nom=nom;
    this->prenom=prenom;
    this->grade=grade;
    this->idpchef=idpchef ;
}

int policier::getidp()
{
    return idp;
}
int policier::getidpchef()
{
    return idpchef;
}
QString policier::getnom()
{
    return nom ;
}
QString policier::getprenom()
{
    return prenom ;
}
QString policier::getgrade()
{
    return grade ;
}




void policier::setidp(int idp)
{
    this->idp=idp;
}
void policier::setnom(QString nom )
{
     this->nom=nom;
}
void policier::setprenom(QString prenom )
{
     this->prenom=prenom;
}
void policier::setgrade(QString grade)
{
    this->grade=grade;
}
void policier::setidpchef(int idpchef)
{
    this->idpchef=idpchef;
}


QSqlQueryModel * policier::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from POLICIER");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("idp"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("grade"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("idpchef"));
    return model;


}
/*
   QSqlQueryModel *policier::afficherparnom(QString q)
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery(" SELECT * FROM POLICIER WHERE nom LIKE '% :q %' ");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("idp"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("grade"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("idpchef"));
     return model;
 }
*/
bool policier::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(idp);
    QString resss= QString::number(idpchef);
    query.prepare("INSERT INTO POLICIER (idp, nom, prenom , grade ,idpchef) "
                  "VALUES (:idp, :nom, :prenom,:grade, :idpchef)");
    query.bindValue(":idp", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":grade", grade);
    query.bindValue(":idpchef", resss);

    return query.exec();

}

bool policier::supprimer(int idp)
{
    QSqlQuery query;
    QString res=QString::number(idp);
    query.prepare("Delete from POLICIER where idp= :idp ");
    query.bindValue(":idp",res);

    return query.exec();
}




