QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajout_reparation.cpp \
    connection.cpp \
    equipements.cpp \
    main.cpp \
    mainwindow.cpp \
    reparations.cpp \
    vehicule.cpp \
    vehicule_modifier_window.cpp

HEADERS += \
    ajout_reparation.h \
    connection.h \
    equipements.h \
    mainwindow.h \
    reparations.h \
    vehicule.h \
    vehicule_modifier_window.h

FORMS += \
    ajout_reparation.ui \
    mainwindow.ui \
    vehicule_modifier_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT+= sql
CONFIG += console
RESOURCES += dark/style.qrc
RESOURCES += light/style.qrc
RESOURCES += DarkOrange/darkorange/darkorange.qrc
QT += core gui \
multimedia
