#ifndef DEMANDES_ADMINISTRATIVES_H
#define DEMANDES_ADMINISTRATIVES_H

#include<QString>
#include<QSqlQueryModel>
#include<QDateTime>

class demandes_administratives
{
public:
    demandes_administratives();
     demandes_administratives(int,QString,QString,QDateTime);

     int getid();
     QString getnom();
     QString gettype();
     QDateTime getDATE_CREATION();


     void setid(int);
     void setnom(QString);
     void settype(QString);
     void setDATE_CREATION( QDateTime);

      bool ajouter_2();

      QSqlQueryModel*afficher();

      bool supprimer(int);

      bool modifier(int);

private:
    int iddem ;
    QString nom,type;
     QDateTime DATE_CREATION;

};

#endif // DEMANDES_ADMINISTRATIVES_H
