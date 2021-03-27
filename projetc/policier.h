#ifndef POLICIER_H
#define POLICIER_H
#include <QString>
#include <QSqlQueryModel>

class policier
{
private :
    int idp , idpchef;
    QString nom , prenom , grade ;



public:

    //constructeurs

     policier();
     policier(int,QString,QString,QString,int);

    //getters
    int getidp();
    int getidpchef();
    QString getnom();
    QString getprenom();
    QString getgrade();

    //setters

    void setidp(int);
    void setidpchef(int);
    void setnom(QString);
    void setprenom(QString);
    void setgrade(QString);

    //functions

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
};

#endif // POLICIER_H
