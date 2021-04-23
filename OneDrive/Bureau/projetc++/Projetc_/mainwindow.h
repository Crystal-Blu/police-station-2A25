#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <citoyen.h>
#include<demandes_administratives.h>
#include <arduino.h>
#include <QVariant>


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
    //void on_pushButton_clicked();



    void on_pushButton_Ajouter_clicked();




    void on_supp_button_clicked();

    void on_update_button_clicked();

    void on_pushButton_Ajouter_2_clicked();

    void on_pushButton_supp_2_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_tab_demande_2_activated(const QModelIndex &index);

    void on_pushButton_2_clicked();









    void on_tab_citoyen_2_activated(const QModelIndex &index);

    void on_tab_citoyen_modifier_activated(const QModelIndex &index);

    void on_lineEdit_17_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_tab_citoyen_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_lineEdit_18_textChanged(const QString &arg1);

    void on_pb_darkmode_clicked();

    void on_pb_darkorange_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;

    Citoyen C ;
    Citoyen c1;
    demandes_administratives d;
    demandes_administratives d1;
    QByteArray data ;
        Arduino A;




};
#endif // MAINWINDOW_H
