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
    int ID_DELIT,ID_CRIMINEL;
    QDate DATE_DELIT;


public:
    //constructeurs
    Delits();
    Delits(int,QDate,QString,QString,int);
    //Getters
    int getid ();
    QString gettype() ;
    QString getdescription ();
    QDate getdate();
    int getidc ();

    //setters

    void settype (QString );
    void setdesciption (QString);
    void setid (int);
    void setdate (QDate);
    void setidc (int) ;

    //fonctionnalite de base
    bool ajouter();
    QSqlQueryModel * afficher ();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * trier ();


};

#endif // DELITS_H
