#include "mainwindow.h"
#include<QDebug>
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test=c.createconnect();
    if(!test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Couldn't establish a connection with the database.\n"
                                "Click ok to exit."), QMessageBox::Ok);
        return a.exec();

}
    else
    {w.show();
    return a.exec();}
}
