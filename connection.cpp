#include "connection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
Connection::Connection()
{

}

bool Connection::createconnect()
{  bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
db.setUserName("walid");//inserer nom de l'utilisateur
db.setPassword("esprit2019");//inserer mot de passe de cet utilisateur




    if (db.open())
    test=true;

        return  test;
}
