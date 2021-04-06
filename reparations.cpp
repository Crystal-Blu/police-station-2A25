#include "reparations.h"

Reparations::Reparations()
{

}

Reparations::Reparations (int id, int mat,QString type_q,QString Desc)
{
    set_id_rep(id);
    set_matricule(mat);
    set_type(type_q);
    set_desc(Desc);
    rep="NON";
}


bool Reparations::ajouter_rep()
{
    QSqlQuery query;
    query.prepare ("insert into DEMANDE_REPARATION (MATRICULE, ID_DEMANDE, TYPE, DESCRIPTION, REPARE) VALUES (:matirucle, :id, :type, :desc, :r)");
    query.bindValue(":matirucle",this->get_matricule());
    query.bindValue(":id",this->get_id_rep());
    query.bindValue(":type",this->get_type());
    query.bindValue(":desc",this->get_desc());
    query.bindValue(":r","NON");
    return query.exec();
}

QSqlQueryModel * Reparations::Afficher_rep()
{
    QSqlQueryModel * modele=new QSqlQueryModel();
    modele->setQuery("select * from demande_reparation");
    modele->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    modele->setHeaderData(1,Qt::Horizontal,QObject::tr("ID"));
    modele->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    /*modele->setHeaderData(3,Qt::Horizontal,QObject::tr("Description"));*/
    modele->setHeaderData(4,Qt::Horizontal,QObject::tr("Réparé ?"));
    return modele;
}

QString Reparations::get_description(int id)
{
    QSqlQuery query;
    query.prepare("select Descritpion from demandes reparation where id_demande=:id");
    query.bindValue(":id",id);
    return query.value(0).toString();
}

bool Reparations::care_repared (int id)
{
    QSqlQuery query;
    query.prepare ("UPDATE DEMANDE_REPARATION set repare=:r where id_demande=:id ");
    query.bindValue(":r","OUI");
    query.bindValue(":id",id);
    return query.exec();
}
bool Reparations::delete_rep(int id)
{
    QSqlQuery query;
    query.prepare("Delete from demande_reparation where id_demande= :id");
    query.bindValue(":id", id);
    return query.exec();
}
