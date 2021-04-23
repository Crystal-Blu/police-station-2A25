QT       += core gui printsupport multimedia serialport quickwidgets  positioning location qml
QT += location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    citoyen.cpp \
    connection.cpp \
    demandes_administratives.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    arduino.h \
    citoyen.h \
    connection.h \
    demandes_administratives.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += sql

RESOURCES += \
    icon.qrc \
    qml.qrc \
    translation.qrc
    RESOURCES += darkorange/darkorange.qrc
    RESOURCES += dark/style.qrc
    RESOURCES += light/style.qrc

DISTFILES += \
    Police.ico

