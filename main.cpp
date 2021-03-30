#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "Connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Connection c; //une seule instance de la classe connexion
    bool test=c.createconnection();//etablir la connexion
    MainWindow w;
    if(test)//si la connexion est etablie
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
        QObject::tr("connection successful.\n"
        "Click Cancel to exit."), QMessageBox::Cancel);

}
    else      //connexion echoue
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
            QObject::tr("connection failed.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
