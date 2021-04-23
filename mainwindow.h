#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "delits.h"
#include "criminels.h"
#include <QMainWindow>
#include <chart.h>
#include<QMediaPlayer>
//QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
//QT_END_NAMESPACE


class QMediaPlayer;


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

    void on_PB_add_c_clicked();

    void on_PB_DEL_C_clicked();

    void on_PB_mod_c_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_trier_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_ouvm_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_mute_clicked();

    void on_volume_valueChanged(int value);

    void on_PB_load_clicked();

    void on_pushButton_trier_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    Delits D1 ;
    Delits H;
    Delits F;
    Criminels C1,C2;
    QMediaPlayer *mMediaPlayer ;
    QMediaPlayer *mmMediaPlayer ;

};
#endif // MAINWINDOW_H
