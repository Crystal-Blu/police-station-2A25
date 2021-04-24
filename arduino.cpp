#include "arduino.h"
#include "ui_arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QSqlQuery>
#include <QSqlDriver>

arduino::arduino(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arduino)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    serial = new QSerialPort;

    /*
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
    */

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // open and configure the serialport
        serial->setPortName(arduino_port_name);
        serial->open(QSerialPort::WriteOnly);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
    }else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}

arduino::~arduino()
{
    if(serial->isOpen()){
        serial->close();
    }
    delete ui;
}




void arduino::updateRGB(QString command)
{
    if(serial->isWritable()){
        serial->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}

void arduino::on_pushButton_testarduino_clicked()
{
    int CODE=ui->lineEdit_testarduino->text().toInt();

    QString CODEstr=QString::number(CODE);
    QSqlQuery query;

          int numRows= 0;
          query.exec("SELECT COUNT(*) FROM DELITS WHERE ID_DELIT  ='"+CODEstr+"'");
          if(query.first())
              numRows = query.value(0).toInt();
          if (numRows==0){
    arduino::updateRGB(QString("r%1").arg(150));
    qDebug() << 150;}
          else{
    arduino::updateRGB(QString("g%1").arg(150));
    qDebug() << 150;
          }
}
