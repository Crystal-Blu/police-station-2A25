#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QFile>
#include <QTranslator>
#include <QInputDialog>








int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTranslator t;

    QStringList languages;

    languages << "français" << "anglais" ;

    QString lang = QInputDialog ::getItem(NULL,"choisir langue","language",languages);

    if (lang == "anglais")
    {
        t.load(":/english.qm");
    }
     if  (lang != "français")

{
        a.installTranslator(&t);
    }



    QFile stylesheetfile("C:/Users/asus/OneDrive/Bureau/Darkeum.qss");
    stylesheetfile.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(stylesheetfile.readAll());
    a.setStyleSheet(stylesheet);








   { Connection c;
    bool test=c.createconnection();
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();}
}
