QT       += core gui printsupport multimedia serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    missions.cpp \
    policier.cpp

HEADERS += \
    arduino.h \
    connection.h \
    mainwindow.h \
    missions.h \
    policier.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += sql
CONFIG += console
RESOURCES += light/style.qrc \
    image.qrc \
    res.qrc
RESOURCES += dark/style.qrc
RESOURCES += darkorange/darkorange.qrc


