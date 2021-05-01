#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class login;
}


class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QObject *parent = nullptr);
    ~login();




private:
    Ui::login *ui;
};

#endif // LOGIN_H
