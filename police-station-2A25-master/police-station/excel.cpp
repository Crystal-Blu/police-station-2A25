#include "excel.h"
#include "ui_excel.h"

excel::excel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::excel)
{
    ui->setupUi(this);
    setWindowTitle("excel");
}

excel::~excel()
{
    delete ui;
}

int excel::getcol() const
{
    return ui->spinBox_excel->value();
}

int excel::getlign() const
{
    return ui->spinBox_excel2->value();
}


void excel::on_buttonBox_accepted()
{
   accept();
}

void excel::on_buttonBox_rejected()
{
 reject();
}

