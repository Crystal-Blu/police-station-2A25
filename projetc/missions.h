#ifndef MISSIONS_H
#define MISSIONS_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
class missions
{
private:
    int idm,idp;
    QString nom,type;
    QDate date_mission ;
public:
    //constructeurs

     missions();
     missions(int,QString,QString,QDate,int);

    //getters
    int getidm();
    QString getnom();
    QString gettype();
    QDate getdate_mission();
    int getidp();

    //setters

    void setidm(int);
    void setnom(QString);
    void settype(QString);
    void setdate_mission(QDate);
    void setidp(int);

    //functions

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
};

#endif // MISSIONS_H
