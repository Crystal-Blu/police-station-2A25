#ifndef VEHICULE_H
#define VEHICULE_H
#include <QString>
#include <QDate>
#include "connection.h"
#include<QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlQueryModel>


class vehicule
{
    QString nom_marque;
    QDate date_achat;
    int idP,Matricule;
public:
    //getters
    QString getmarque () {return this->nom_marque;};
    int getidp() {return this->idP;};
    int getmatricule() {return this->Matricule;};
    QDate getdate(){return this->date_achat;};
    //setters
    void SetMatricule (int matricule){this->Matricule=matricule;};
    void Setnom_marque (QString nom_marque){this->nom_marque=nom_marque;};
    void SetDate (QDate Date_A){this->date_achat=Date_A;};
    void SetidP (int idp){this->idP=idp;};
    //constructors
    vehicule();
    vehicule(int Matricule,QString Marque,QDate date_achat,int idP);
    //fucntions
    bool ajouter_vehicule();
    QSqlQueryModel * afficher_vehicules();
    bool modifier_vehicule();
    bool delete_vehicule(int matricule);
    bool verify_Police_id(int id);
    bool verify_matricule(int mat);

};

#endif // VEHICULE_H
