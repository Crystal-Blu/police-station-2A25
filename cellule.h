#ifndef CELLULE_H
#define CELLULE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Cellule
{
public:
    Cellule();
    Cellule(int,int,int,int);
    int getid();
    int getnbre_det();
    int getnbre_det_max();
    int getnbre_lit();

    void setid(int);
    void setnbre_det(int);
    void setnbre_det_max(int);
    void setnbre_lit(int);

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);
     bool modifier(int);

private:
    int id,nbre_det,nbre_det_max,nbre_lit ;

};

#endif // CELLULE_H
