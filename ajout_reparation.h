#ifndef AJOUT_REPARATION_H
#define AJOUT_REPARATION_H

#include <QMainWindow>

namespace Ui {
class ajout_reparation;
}

class ajout_reparation : public QMainWindow
{
    Q_OBJECT

public:
    explicit ajout_reparation(QWidget *parent = nullptr);
    ~ajout_reparation();

private:
    Ui::ajout_reparation *ui;
};

#endif // AJOUT_REPARATION_H
