#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>

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
    qry.prepare( " select * from user_police where username=:username AND password=:pwd");
    qry.bindValue(":username",getusername());
    qry.bindValue(":pwd",getpassword());
    if(qry.exec( ))
    {
        while(qry.next())
    {
            accept();
    }
    }


}

void login::on_pb_logincancel_clicked()
{
   reject();
}
