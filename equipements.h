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
#include "reparations.h"
#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H



class Equipements
{
    int IDEQ;
    int matricule;
    QString type_eq;
public:
    //constructors
    Equipements();
    Equipements (int IDEQQ, int mat,QString type_q);
    //Setters
    void set_ideq(int ideq){this->IDEQ=ideq; };
    void set_matricule(int mat){this->matricule=mat;};
    void set_type_eq (QString type_eqq) {this->type_eq=type_eqq;};
    //getters
    int get_ideq (){return this->IDEQ;};
    int get_matricule (){return this->matricule;};
    QString get_type() {return this->type_eq;};
    //functions
    bool ajouter_Equipements();
    QSqlQueryModel * afficher_equipments();
    bool delete_Equipments(int id);
    bool modifier_Equipments();
    //variables
    vehicule V();


};

#endif // EQUIPEMENTS_H
