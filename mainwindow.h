#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "vehicule.h"
#include "vehicule_modifier_window.h"
#include "equipements.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vehicule_modifier_window create_newwindow(vehicule_modifier_window WM);
    vehicule_modifier_window WM;



private slots:
    void on_pushButton_clicked();

    void on_ajouter_clicked();

    void on_Refresh_clicked();

    int on_Vehicule_table_activated(const QModelIndex &index);


    void on_Delete_button_clicked();

    void on_Modif_btton_clicked();



    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_13_clicked();

    int on_Equipemen_table_activated(const QModelIndex &index);

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    vehicule V;
    Equipements E;
};
#endif // MAINWINDOW_H