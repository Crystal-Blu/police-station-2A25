 #ifndef DEMANDES_ADMINISTRATIVES_H
#define DEMANDES_ADMINISTRATIVES_H

#include<QString>
#include<QSqlQueryModel>
class demandes_administratives
{
public:
    demandes_administratives();
     demandes_administratives(int,QString,QString);

     int getid();
     QString getnom();
     QString gettype();


     void setid(int);
     void setnom(QString);
     void settype(QString);

      bool ajouter_2();

      QSqlQueryModel*afficher();

      bool supprimer(int);

      bool modifier(int);

private:
    int id ;
    QString nom,type;

};

#endif // DEMANDES_ADMINISTRATIVES_H
