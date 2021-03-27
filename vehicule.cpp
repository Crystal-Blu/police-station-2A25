#include "vehicule.h"
#include "connection.h"
#include <QSqlQuery>
#include <QDebug>
vehicule::vehicule()
{

};
vehicule::vehicule(int Matricule,QString Marque,QDate date_achat,int idP)
{
    this->idP=idP;
    this->Matricule=Matricule;
    this->nom_marque=Marque;
    this->date_achat=date_achat;
};
bool vehicule::ajouter_vehicule()
{
    QSqlQuery query;
    query.prepare ("insert into vehicules values(:nom_marque , :date_achat, :idp) where matricule = :matricule");
    query.bindValue(":nom_marque",this->nom_marque);
    query.bindValue(":matricule",this->Matricule);
    query.bindValue(":date_achat",this->date_achat);
    query.bindValue(":idp",this->idP);
    query.exec();
};
QSqlQueryModel * vehicule::afficher_vehicules()
{
    QSqlQueryModel * modele=new QSqlQueryModel();
    modele->setQuery("select * from vehicules");
    modele->setHeaderData(0,Qt::Horizontal,QObject::tr("Nom Marque"));
    modele->setHeaderData(1,Qt::Horizontal,QObject::tr("Matricule"));
    modele->setHeaderData(2,Qt::Horizontal,QObject::tr("Date D'achat"));
    modele->setHeaderData(3,Qt::Horizontal,QObject::tr("ID POLICIER"));
    return modele;
};
bool vehicule::delete_vehicule(int matricule)
{
    QSqlQuery query;
    query.prepare("Delete from vehicules where matricule= :matricule");
    query.bindValue(":matricule", matricule);
    return query.exec();
};

bool vehicule::modifier_vehicule()
{
    QSqlQuery query;
    QString res = QString::number(Matricule);
    query.prepare ("UPDATE vehicules set nom_marque=:nom_marque, date_achat=:date_achat, idp=:idp where matricule=:matricule");
    query.bindValue(":matricule",Matricule);
    query.bindValue(":nom_marque",nom_marque);
    query.bindValue(":idp",idP);
    query.bindValue(":date_achat",date_achat);
    query.exec();
    qDebug() << query.lastError();
};
