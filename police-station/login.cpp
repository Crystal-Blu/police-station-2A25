#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QMessageBox>
#include<QIntValidator>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    //setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowFlags ( Qt::CustomizeWindowHint | Qt::WindowTitleHint );
/*
     if(ui->le_loginusername->text().isEmpty() or  ui->le_loginpassword->text().isEmpty()  )
    {
        ui->pb_loginok->setDisabled(1);

    }
    else
    {
        ui->pb_loginok->setDisabled(0);
    }
*/
     ui->le_loginpassword->setValidator ( new QIntValidator(0, 100, this));
     ui->le_loginusername->setMaxLength(20);




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
   exit(EXIT_FAILURE);
}
