#ifndef CRIMINELS_H
#define CRIMINELS_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
#include <QString>

class Criminels
{
private:
    QString NOM_CRIMINEL , PRENOM_CRIMINEL;
    int ID_CRIMINEL , AGE_CRIMINEL ;

public:
    //constructeurs
    Criminels();
    Criminels(int,int,QString,QString);
    //Getters
    int getidc ();
    QString getnom() ;
    QString getprenom ();
    int getage();

    //setters

    void setidc (int );
    void setprenom (QString);
    void setage (int);
    void setnom (QString);


    //fonctionnalite de base
    bool ajouter_c();
    QSqlQueryModel * afficher_c ();
    bool supprimer_c(int);
    bool modifier_c(int);
    bool Rechercher_c();


};

#endif // CRIMINELS_H
