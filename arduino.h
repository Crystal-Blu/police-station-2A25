#ifndef ARDUINO_H
#define ARDUINO_H

#include <QDialog>

#include <QSerialPort>

namespace Ui {
class arduino;
}

class arduino : public QDialog
{
    Q_OBJECT

public:
    explicit arduino(QWidget *parent = 0);
    ~arduino();

private slots:



    void updateRGB(QString);

    void on_pushButton_testarduino_clicked();

private:
    Ui::arduino *ui;
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};
#endif // ARDUINO_H
