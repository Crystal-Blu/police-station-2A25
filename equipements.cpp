#include "equipements.h"
Equipements::Equipements()
{

}

Equipements::Equipements (int IDEQQ, int mat,QString type_q)
{
    this->set_ideq(IDEQQ);
    this->set_matricule(mat);
    this->set_type_eq(type_q);
}


bool Equipements::ajouter_Equipements()
{
    QSqlQuery query;
    query.prepare ("insert into equipements (ideqp,matricule,type) values(:id,:matricule,:type)");
    query.bindValue(":id",this->IDEQ);
    query.bindValue(":matricule",this->matricule);
    query.bindValue(":type",this->type_eq);
    query.exec();
}

QSqlQueryModel * Equipements::afficher_equipments()
{
    QSqlQueryModel * modele=new QSqlQueryModel();
    modele->setQuery("select * from equipments");
    modele->setHeaderData(0,Qt::Horizontal,QObject::tr("ID Equipement"));
    modele->setHeaderData(1,Qt::Horizontal,QObject::tr("Matricule"));
    modele->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    return modele;
}

bool Equipements::delete_Equipments(int id)
{
    QSqlQuery query;
    query.prepare("Delete from equipments where ideqp= :ideq");
    query.bindValue(":ideq", id);
    return query.exec();
}

bool Equipements::modifier_Equipments()
{
    QSqlQuery query;
    query.prepare ("UPDATE equipments set matricule=:matricule, type=:type where ideqp=:id");
    query.bindValue(":ideqp",this->IDEQ);
    query.bindValue(":matricule",matricule);
    query.bindValue(":type",type_eq);
    return query.exec();
}
