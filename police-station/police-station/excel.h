#ifndef EXCEL_H
#define EXCEL_H

#include <QDialog>

namespace Ui {
class excel;
}

class excel : public QDialog
{
    Q_OBJECT

public:
    explicit excel(QWidget *parent = nullptr);
    ~excel();
    int getlign() const ;
    int getcol() const ;



private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::excel *ui;
};

#endif // EXCEL_H
