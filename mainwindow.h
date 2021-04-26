#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cellule.h>
#include <detention.h>
#include <arduino.h>


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
    void on_pushButton_supp_cel_clicked();

    void on_pushButton_ajouter_cel_clicked();

    void on_pushButton_modifier_cel_clicked();

    void on_pushButton_ajouter_det_clicked();

    void on_pushButton_modifier_det_clicked();

    void on_pushButton_supprimer_det_clicked();

    void on_pushButton_metier_pdf_clicked();

    void on_le_recherche_maya_textChanged(const QString &arg1);

    void on_pushButton_maya_1_clicked();

    void on_pushButton_maya_2_clicked();

    void on_pushButton_maya_3_clicked();

    void on_pushButton_maya_4_clicked();

    void on_pushButton_maya_5_clicked();

    void on_pushButton_maya_6_clicked();


    void on_pushButton_md_sombre_clicked();

    void on_pushButton_md_clair_clicked();

    void on_pushButton_md_sombre_orange_clicked();

    void on_pushButton_md_original_clicked();

    void on_pushButton_lumiere_act_clicked();

    void on_pushButton_lumiere_desact_clicked();

    void update_label_lumiere();




private:
    Ui::MainWindow *ui;
    Cellules C ;
    Cellules C1 ;
    detentions D ;
    detentions D1;
    QByteArray data ;
    Arduino A;

};
#endif // MAINWINDOW_H
