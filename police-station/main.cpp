#include "mainwindow.h"
#include<QDebug>
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include<QFile>
#include "login.h"
#include<QTranslator>
#include<QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;

    QStringList languages;

    languages << "français" << "anglais" ;

    QString lang = QInputDialog ::getItem(NULL,"choisir langue","langue",languages);

    if (lang == "anglais")
    {
        t.load(":/english.qm");
    }
     if  (lang != "français")

{
        a.installTranslator(&t);
    }
    MainWindow w;
    login L;
    Connection c;

    bool test=c.createconnect();
    if(!test)
    {
        //exit(EXIT_FAILURE);
        //w.show();

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Couldn't establish a connection with the database. Can't login till database is working Click ok to exit."), QMessageBox::Ok);
        //L.exec();
        return a.exec();

}
    else
    {if (L.exec()==QDialog::Accepted)
       w.show();

    }
    return a.exec();





}
