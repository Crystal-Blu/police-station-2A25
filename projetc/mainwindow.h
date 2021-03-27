#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "policier.h"
#include <QMainWindow>

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

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pb_addpolice_clicked();

    void on_tableViewpolice_activated(const QModelIndex &index);

    void on_pb_modifiepolice_clicked();

private:
    Ui::MainWindow *ui;
    policier police;
};
#endif // MAINWINDOW_H
