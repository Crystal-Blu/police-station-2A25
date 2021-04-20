QT       += core gui printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    cellule.cpp \
    connection.cpp \
    detention.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    arduino.h \
    cellule.h \
    connection.h \
    detention.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += sql
CONFIG += console


RESOURCES += dark/style.qrc
RESOURCES += light/style.qrc
RESOURCES += DarkOrange/darkorange/darkorange.qrc
