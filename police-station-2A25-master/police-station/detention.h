#ifndef DETENTION_H
#define DETENTION_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class detentions
{
public:
    detentions();
        detentions(int,QDate,QDate,QString,int,int);
        int getiddet();
        QDate getdate_entree();
        QDate getdate_sortie();
        QString getraison();
        int getidcel();
        int getidp();

        void setiddet(int);
        void setdate_entree(QDate);
        void setdate_sortie(QDate);
        void setraison(QString);
        void setidcel(int);
        void setidp(int);

        bool ajouter();
        QSqlQueryModel*afficher();
        bool supprimer(int);
         bool modifier(int);

private:
    int iddet,idcel,idp;
    QDate date_entree,date_sortie;
    QString raison;
};

#endif // DETENTION_H
