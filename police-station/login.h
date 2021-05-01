#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QString getusername()  ;
    QString getpassword()  ;
    bool getaccept(){return accepted;}  ;

private:
    Ui::login *ui;
    bool accepted=false;


private slots:
    void on_pb_loginok_clicked();
    void on_pb_logincancel_clicked();
};

#endif // LOGIN_H


