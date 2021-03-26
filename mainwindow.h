#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cellule.h>
#include <detention.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_supp1_clicked();

    void on_pushButton_ajouter1_clicked();

    void on_pushButton_modifier1_clicked();

    void on_pushButton_ajouter2_clicked();

    void on_pushButton_modifier2_clicked();

    void on_pushButton_supprimer2_clicked();

private:
    Ui::MainWindow *ui;
    Cellules C ;
    Cellules C1 ;
    detentions D ;
    detentions D1;

};
#endif // MAINWINDOW_H
