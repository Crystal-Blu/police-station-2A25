QT       += core gui multimedia printsupport
QT       += sql
QT += charts serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Connection.cpp \
    arduino.cpp \
    chart.cpp \
    charttype.cpp \
    criminels.cpp \
    delits.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Connection.h \
    arduino.h \
    chart.h \
    charttype.h \
    criminels.h \
    delits.h \
    mainwindow.h

FORMS += \
    chart.ui \
    charttype.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
CONFIG += console
