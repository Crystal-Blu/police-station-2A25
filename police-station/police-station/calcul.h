#ifndef CALCUL_H
#define CALCUL_H

#include <QDialog>

namespace Ui {
class Calcul;
}

class Calcul : public QDialog
{

    Q_OBJECT

public:
    explicit Calcul(QWidget *parent = nullptr);
    ~Calcul();

private:
    Ui::Calcul *ui;

private slots :
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
};

#endif

