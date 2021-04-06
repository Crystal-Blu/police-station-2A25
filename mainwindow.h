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

    void on_pushButton_clicked();

    void on_le_recherche_textChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::MainWindow *ui;
    Cellules C ;
    Cellules C1 ;
    detentions D ;
    detentions D1;

};
#endif // MAINWINDOW_H
