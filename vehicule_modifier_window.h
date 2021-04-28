#ifndef VEHICULE_MODIFIER_WINDOW_H
#define VEHICULE_MODIFIER_WINDOW_H

#include <QDialog>
#include "vehicule.h"

namespace Ui {
class vehicule_modifier_window;
}

class vehicule_modifier_window : public QDialog
{
    Q_OBJECT

public:
    explicit vehicule_modifier_window(QWidget *parent = nullptr);
    ~vehicule_modifier_window();
    vehicule vehicule_M;
    void remplir(QString matricule,QString idp, QDate date_a,QString nom_marque);

private slots:
    void on_pushButton_clicked();

private:
    Ui::vehicule_modifier_window *ui;
};

#endif // VEHICULE_MODIFIER_WINDOW_H
