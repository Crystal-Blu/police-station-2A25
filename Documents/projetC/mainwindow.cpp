#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.cpp"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>

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
    Connection conn;
    QSqlQueryModel * model=new QSqlQueryModel();
}
