#include "ajout_reparation.h"
#include "ui_ajout_reparation.h"

ajout_reparation::ajout_reparation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ajout_reparation)
{
    ui->setupUi(this);
}

ajout_reparation::~ajout_reparation()
{
    delete ui;
}
