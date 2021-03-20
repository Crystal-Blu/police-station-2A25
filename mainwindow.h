#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cellule.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_ajouter_clicked();

    void on_pushButton_supp1_clicked();

    void on_pushButton_ajouter1_clicked();

    void on_pushButton_modifier1_clicked();

private:
    Ui::MainWindow *ui;
    Cellule C ;
    Cellule C1 ;


};
#endif // MAINWINDOW_H
