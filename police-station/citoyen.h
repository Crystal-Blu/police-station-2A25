#ifndef CITOYEN_H
#define CITOYEN_H

#include <QString>
#include<QSqlQueryModel>
#include <QDate>
#include<QByteArray>

class Citoyen
{

public:
    Citoyen();
    Citoyen(int,QString,QString,QString,  QByteArray ,QDate,QString);
    int getCIN();
    QString getnom();
    QString getprenom();
    QString getadresse();
     QByteArray getphoto();
    QDate getdate();

    void setCIN(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
  void setphoto(QByteArray);
    void setdate(QDate);

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);
     bool modifier(int);
     void set_path(QString path){path_image=path;};
     QString get_path(){return path_image;};

private:
    int CIN ;
    QString nom,prenom,adresse,path_image;
    QDate DATE_NAISSANCE;
    QByteArray inByteArray ;
};





#endif // CITOYEN_H
