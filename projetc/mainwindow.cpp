#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-2);

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-1);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-1);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-1);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-3);

}

void MainWindow::on_pushButton_15_clicked()
{
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-3);

}

void MainWindow::on_pushButton_16_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-1);

}

void MainWindow::on_pushButton_17_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-1);

}

void MainWindow::on_pushButton_18_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-1);

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-2);

}

void MainWindow::on_pushButton_19_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-3);

}

void MainWindow::on_pushButton_20_clicked()
{
    ui->tabWidget_3->setCurrentIndex(ui->tabWidget_3->count()-3);

}
