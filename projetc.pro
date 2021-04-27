QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajout_reparation.cpp \
    arduino.cpp \
    cellule.cpp \
    chart.cpp \
    charttype.cpp \
    connection.cpp \
    criminels.cpp \
    delits.cpp \
    detention.cpp \
    equipements.cpp \
    main.cpp \
    mainwindow.cpp \
    missions.cpp \
    policier.cpp \
    reparations.cpp \
    vehicule.cpp \
    vehicule_modifier_window.cpp

HEADERS += \
    ajout_reparation.h \
    arduino.h \
    cellule.h \
    chart.h \
    charttype.h \
    connection.h \
    criminels.h \
    delits.h \
    detention.h \
    equipements.h \
    mainwindow.h \
    missions.h \
    policier.h \
    reparations.h \
    vehicule.h \
    vehicule_modifier_window.h

FORMS += \
    ajout_reparation.ui \
    chart.ui \
    charttype.ui \
    mainwindow.ui \
    vehicule_modifier_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT+= serialport
QT+= sql
CONFIG += console


RESOURCES += light/style.qrc \
    darktheme.qrc \
    images.qrc
RESOURCES += res.qrc


RESOURCES += DarkOrange/darkorange/darkorange.qrc
QT += core gui \
multimedia

QMAKE_CXXFLAGS += -std=gnu++14

RC_ICONS = Police.ico

DISTFILES += \
    Police.png
