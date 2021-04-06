#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "policier.h"
#include "missions.h"
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

    void on_pb_addpolice_clicked();

    void on_tableViewpolice_activated(const QModelIndex &index);

    void on_pb_modifiepolice_clicked();

    void on_tableViewmissions_activated(const QModelIndex &index);

    void on_pb_missionsdelete_clicked();

    void on_pb_missionsmodifier_clicked();

    void on_pb_mission_clicked();

    void on_le_searchplice_textChanged(const QString &arg1);

    void on_pb_policetaketomodifier_clicked();

    void on_pb_policesupprimer_clicked();

    void on_pb_policetaketoadd_clicked();

    void on_pb_missionstaketoadd_clicked();

    void on_pb_missionadd_clicked();

    void on_pb_missioninfoprint_clicked();

    void on_pb_darkmode_clicked();

    void on_pb_lightmode_clicked();

    void on_pb_darkorange_clicked();

    void on_pb_defaultmode_clicked();

    void on_le_grade_textEdited(const QString &arg1);

    void on_le_policeid_textEdited(const QString &arg1);

    void on_le_prenompolice_textEdited(const QString &arg1);

    void on_le_nompolice_textEdited(const QString &arg1);

    void on_le_chefid_textEdited(const QString &arg1);


    void on_le_grademodifier_textEdited(const QString &arg1);

    void on_le_prenommodifier_textEdited(const QString &arg1);


    void on_le_nompolicemodifier_textEdited(const QString &arg1);

    void on_le_chefidmodifier_textEdited(const QString &arg1);

    void on_le_missionidadd_textEdited(const QString &arg1);

    void on_le_missionnameadd_textEdited(const QString &arg1);

    void on_le_missiontypeadd_textEdited(const QString &arg1);

    void on_le_missionpoliceidadd_textEdited(const QString &arg1);

    void on_de_missiondateadd_dateChanged(const QDate &date);

    void on_le_missionnamemodifier_textEdited(const QString &arg1);

    void on_le_missiontypemodifier_textEdited(const QString &arg1);

    void on_le_missionpoliceidmodifier_textEdited(const QString &arg1);

    void on_de_missiondatemodifier_userDateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
    policier police;
    missions mission;
};
#endif // MAINWINDOW_H
