#ifndef CITOYEN_H
#define CITOYEN_H

#include <QString>
#include<QSqlQueryModel>
#include <QDate>

class Citoyen
{
public:
    Citoyen();
    Citoyen(int,QString,QString,QString,QDate);
    int getCIN();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QDate getdate();
    void setCIN(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setdate(QDate);
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);
     bool modifier(int);

private:
    int CIN ;
    QString nom,prenom,adresse;
    QDate date;
};

#endif // CITOYEN_H
