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
    void on_pushButton_ajoutdelit_clicked();

    void on_pushButton_supprimerdelit_clicked();

    void on_pushButton_modifierdelit_clicked();

    void on_pushButton_ajoutcriminel_clicked();

    void on_pushButton_supprimercriminel_clicked();

    void on_pushButton_modifiercriminel_clicked();

    void on_pushButton_rechercherdelit_clicked();

    void on_pushButton_recherchercriminel_clicked();

    void on_pushButton_recherchercriminel2_clicked();

    void on_pushButton_trierdelittype_clicked();

    void on_pushButton_trierdelitdate_clicked();

    void on_pushButton_chart1_clicked();

    void on_pushButton_ouvm_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_mute_clicked();

    void on_volume_valueChanged(int value);

    void on_PB_load_clicked();

    void on_pushButton_chart2_clicked();

    void on_pushButton_exportercriminel_clicked();

    void on_pushButton_changerlight_clicked();

    void on_pushButton_changerdark_clicked();

    void on_pushButton_changerorange_clicked();

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
