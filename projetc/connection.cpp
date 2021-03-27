#include "connection.h"

connection::connection()
{

}

bool connection::createconnection()

{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
db.setUserName("yassin");//inserer nom de l'utilisateur
db.setPassword("esprit2019 ");//inserer mot de passe de cet utilisateur

if (db.open())test=true;


    return  test;
}
void connection::closeconnection(){db.close();}
