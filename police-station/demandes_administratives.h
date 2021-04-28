#ifndef DEMANDES_ADMINISTRATIVES_H
#define DEMANDES_ADMINISTRATIVES_H

#include<QString>
#include<QSqlQueryModel>
#include<QDateTime>

class demandes_administratives
{
public:
    demandes_administratives();
     demandes_administratives(int,int,int,QString,QString,QDate);

     int getid();
    int getidp();
    int getcin();
     QString getnom();
     QString gettype();
     QDate getDATE_CREATION();


     void setid(int);
     void setidp(int);
     void setcin(int);
     void setnom(QString);
     void settype(QString);
     void setDATE_CREATION( QDate);

      bool ajouter_2();

      QSqlQueryModel*afficher();

       QSqlQueryModel*afficher_combo();
        QSqlQueryModel*afficher_combo_2();

      bool supprimer(int);

      bool modifier(int);

private:
    int iddem ;
    int idp ;
    int cin ;
    QString nom,type;
     QDate DATE_CREATION;

};

#endif // DEMANDES_ADMINISTRATIVES_H
