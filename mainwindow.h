#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "delits.h"

#include <QMainWindow>

//QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_6_clicked();

    void on_supprimerPb_3_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;
    Delits D1 ;
    Delits H;
    Delits F;
};
#endif // MAINWINDOW_H
