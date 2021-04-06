#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "vehicule.h"
#include "vehicule_modifier_window.h"
#include "equipements.h"
#include "reparations.h"
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
    QSqlQueryModel *get_policiers();
    void updateaffichagevehicule();
    void updateaffichageeq();


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

    void on_Assign_Police_clicked();
    
    void on_Demande_rep_clicked();
    
    void on_pushButton_15_clicked();

    void on_tableView_4_activated(const QModelIndex &index);

    void on_ajouter_2_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_16_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);



    void on_pushButton_14_clicked();

    void on_radioButton_15_clicked();

    void on_radioButton_18_clicked();

    void on_radioButton_17_clicked();

    void on_radioButton_16_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_21_clicked();

    void on_radioButton_22_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_10_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_11_clicked();



    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();


private:
    Ui::MainWindow *ui;
    vehicule V;
    Equipements E;
    Reparations R;
};
#endif // MAINWINDOW_H
