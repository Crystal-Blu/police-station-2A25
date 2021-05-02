#include "arduino.h"
#include <QtDebug>




int Arduino::connect_arduino()
{
int AVA=0;

    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts())
    {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
          if( serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id )
          {
           arduino_is_available= true ;
           if (serial_port_info.portName()==port_chosen)
           {
               arduino_port_name=serial_port_info.portName();
               AVA=1;
           }
          }
        }
    }
    qDebug()<< "arduino_port_name is :" << arduino_port_name;
    if (arduino_is_available)
    {
     serial.setPortName(arduino_port_name);
     if (serial.open(QSerialPort::ReadWrite))
     {
            serial.setBaudRate(QSerialPort::Baud9600);
            serial.setDataBits(QSerialPort::Data8);
            serial.setParity(QSerialPort::NoParity);
            serial.setStopBits(QSerialPort::OneStop);
            serial.setFlowControl(QSerialPort::NoFlowControl);
            return 0 ;
    }



}
    if  (AVA==0)
    return -1;

}

int Arduino::close_arduino(){
    if(serial.isOpen()){
        serial.close();
        return 0 ;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino()
{
    if (serial.isReadable()){
        data=serial.readAll();
                return data;
    }
}

int Arduino::write_to_arduino(QByteArray d)
{
    if(serial.isWritable()){
        serial.write(d);
    } else {
        qDebug() << "Could't write to serial";

    }
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}


QSerialPort* Arduino::getserial()
{
    return &serial;
}

