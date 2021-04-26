#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "vehicule.h"
#include "vehicule_modifier_window.h"
#include "equipements.h"
#include <QtMultimedia/QMediaPlayer>
#include "reparations.h"
#include <QSystemTrayIcon>
#include "arduino.h"
#include "policier.h"
#include "missions.h"
#include "detention.h"
#include "cellule.h"
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
    void remplir();
    void remplir_vehi();
    void remplir_equipements();


private slots:
    void on_pushButton_clicked();

    void on_ajouter_clicked();

    void on_Refresh_clicked();

    int on_Vehicule_table_activated(const QModelIndex &index);


    void on_Delete_button_clicked();

    void on_Modif_btton_clicked();

    int on_Equipemen_table_activated(const QModelIndex &index);


    void on_Assign_Police_clicked();
    
    void on_Demande_rep_clicked();
    
    void on_pushButton_15_clicked();


    void on_ajouter_2_clicked();



    void on_radioButton_15_clicked();

    void on_radioButton_18_clicked();

    void on_radioButton_17_clicked();

    void on_radioButton_16_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_10_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_21_clicked();

    void on_radioButton_22_clicked();

    void check_voiture_repare();
    void print_test();

    void on_recherche_eq_textChanged(const QString &arg1);

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_id_eq_edit_textChanged(const QString &arg1);

    void on_Matricule_eq_edit_textChanged(const QString &arg1);

    void on_type_edit_textChanged(const QString &arg1);

    void on_MatriculeEdit_2_textChanged(const QString &arg1);

    void on_idreparation_textChanged(const QString &arg1);

    void on_type_reparation_cursorPositionChanged(int arg1, int arg2);

    void on_textEdit_textChanged();

    void on_MatriculeEdit_textChanged(const QString &arg1);

    void on_modeleEdit_textChanged(const QString &arg1);

    void on_idpedit_textChanged(const QString &arg1);

    void on_pushButton_27_clicked();

    void check_vehicules_number();

    void check_equipements_number();

    void on_pushButton_6_clicked();

    void update_label();

    void on_rechercher_vehicule_edit_textChanged(const QString &arg1);

    void on_cancelbtnvehicules_clicked();

    void on_Chech_matricule_vehi_clicked();

    void on_check_idp_vehi_clicked();

    void on_tableView_reparations_activated(const QModelIndex &index);

    void on_declarerepare_clicked();

    void on_supprimer_reparation_clicked();


    void on_ajouter_equipement_clicked();

    void on_Print_pdf_vehicules_clicked();

    void on_print_pdf_equipements_clicked();

    void on_refresh_equipements_clicked();

    void on_supprimer_equipements_clicked();

    void on_modifier_equip_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_stateChanged(int arg1);

    void on_test_clicked();

    void on_checkBox_2_stateChanged(int arg1);

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

    void on_pb_refreshpolicetable_clicked();

    void on_pb_missionrefresh_clicked();

    void on_pushButton_maya_1_clicked();
    void on_pushButton_supp_cel_clicked();

    void on_pushButton_ajouter_cel_clicked();

    void on_pushButton_modifier_cel_clicked();

    void on_pushButton_ajouter_det_clicked();

    void on_pushButton_modifier_det_clicked();

    void on_pushButton_supprimer_det_clicked();

    void on_pushButton_metier_pdf_clicked();

    void on_le_recherche_maya_textChanged(const QString &arg1);
    void on_pushButton_maya_2_clicked();

    void on_pushButton_maya_3_clicked();

    void on_pushButton_maya_4_clicked();

    void on_pushButton_maya_5_clicked();

    void on_pushButton_maya_6_clicked();

    void on_pushButton_lumiere_act_clicked();

    void on_pushButton_lumiere_desact_clicked();

    void update_label_lumiere();


    void on_rafraichir_maya1_clicked();

    void on_rafraichir_maya2_clicked();

private:
    QByteArray data ;
        Arduino A;
    Ui::MainWindow *ui;
    vehicule V;
    Equipements E;
    Reparations R;
    QMediaPlayer *player = new QMediaPlayer;
    QSqlDriver * Driver();
    QSystemTrayIcon *mySystemTrayIcon;
    int count,count_vehicules,count_equipements;
    int N=0;
    int id_policier=1;
    QString code;
    int volume=100;
    int arduino_connected;
    policier police;
    missions mission;
    Cellules C ;
    Cellules C1 ;
    detentions D ;
    detentions D1;

};
#endif // MAINWINDOW_H
