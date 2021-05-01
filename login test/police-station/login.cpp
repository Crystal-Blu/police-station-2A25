#include "login.h"
#include "ui_login.h"

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
    accept();

}

void login::on_pb_logincancel_clicked()
{
   reject();
}
