#ifndef CELLULE_H
#define CELLULE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Cellules
{
public:
    Cellules();
    Cellules(int,int,int,int);
    int getidcel();
    int getnombre_det();
    int getnombre_det_max();
    int getnombre_lit();

    void setidcel(int);
    void setnombre_det(int);
    void setnombre_det_max(int);
    void setnombre_lit(int);

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);
     bool modifier(int);

     void ajout_det(int);

private:
    int idcel,nombre_lit,nombre_det,nombre_det_max ;

};

#endif // CELLULE_H
