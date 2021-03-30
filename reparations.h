#ifndef REPARATIONS_H
#define REPARATIONS_H
#include <QString>
#include <QDate>
#include "connection.h"
#include<QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include "vehicule.h"
#include "equipements.h"
#include <QSqlQueryModel>

class Reparations
{
    int matricule;
    int Id_Rep;
    QString Type;
    QString Description;
    QString rep;


public:
    //constructors
    Reparations();
    Reparations(int,int,QString,QString);
    //getters
    int get_matricule(){return matricule;};
    int get_id_rep(){return Id_Rep;}
    QString get_type(){return Type;}
    QString get_desc(){return Description;}
    //setters
    void set_matricule(int mat){matricule=mat;};
    void set_id_rep(int id){Id_Rep=id;}
    void set_type(QString t){Type=t;};
    void set_desc(QString dec){Description=dec;}
    //function
    bool ajouter_rep();
    QSqlQueryModel * Afficher_rep();
    bool modifier_rep();
    QString get_description(int id);
    bool care_repared (int id);
    bool delete_rep(int id);
};

#endif // REPARATIONS_H
