#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("Login");


}

login::~login()
{
    delete ui;
}

QString login::getusername()
{
    return ui->le_loginusername->text();
}

QString login::getpassword()
{
    return ui->le_loginpassword->text();
}


void login::on_pb_loginok_clicked()
{
    QSqlQuery qry;
    qry.prepare( " select * from POLICIER where nom=:username AND idp=:pwd");
    qry.bindValue(":username",getusername());
    qry.bindValue(":pwd",getpassword());
    if(qry.exec( ))
    {
        while(qry.next())
    {
            accept();
    }

    }
    else
        QMessageBox::critical(nullptr,QObject::tr(" LOGIN "), QObject::tr("wrong username or password. \n" "Clic ok to exit."),QMessageBox::Ok);


}

void login::on_pb_logincancel_clicked()
{
   reject();
}
