#ifndef DELITS_H
#define DELITS_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
#include <QString>

class Delits
{
private:
    QString TYPE_DELIT , DESCRIPTION_DELIT;
    int ID_DELIT;
    QDate DATE_DELIT;


public:
    //constructeurs
    Delits();
    Delits(int,QDate,QString,QString);
    //Getters
    int getid ();
    QString gettype() ;
    QString getdescription ();
    QDate getdate();

    //setters

    void settype (QString );
    void setdesciption (QString);
    void setid (int);
    void setdate (QDate);


    //fonctionnalite de base
    bool ajouter();
    QSqlQueryModel * afficher ();
    bool supprimer(int);
    bool modifier(int);


};

#endif // DELITS_H
