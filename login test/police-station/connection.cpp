#include "connection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
Connection::Connection()
{

}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

        //db.setHostName("26.215.175.171");
        //db.setPort(1521);
        bool test=false;
    db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
    db.setUserName("yassin");//inserer nom de l'utilisateur
    db.setPassword("esprit2019");//inserer mot de passe de cet utilisateur


    if (db.open())
    test=true;

        return  test;
}
