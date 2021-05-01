QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajout_reparation.cpp \
    arduino.cpp \
    calculer.cpp \
    cellule.cpp \
    chart.cpp \
    charttype.cpp \
    citoyen.cpp \
    connection.cpp \
    criminels.cpp \
    delits.cpp \
    demandes_administratives.cpp \
    detention.cpp \
    equipements.cpp \
    excel.cpp \
    login.cpp \
    mailing/emailaddress.cpp \
    mailing/mimeattachment.cpp \
    mailing/mimecontentformatter.cpp \
    mailing/mimefile.cpp \
    mailing/mimehtml.cpp \
    mailing/mimeinlinefile.cpp \
    mailing/mimemessage.cpp \
    mailing/mimemultipart.cpp \
    mailing/mimepart.cpp \
    mailing/mimetext.cpp \
    mailing/quotedprintable.cpp \
    mailing/smtpclient.cpp \
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
    calculer.h \
    cellule.h \
    chart.h \
    charttype.h \
    citoyen.h \
    connection.h \
    criminels.h \
    delits.h \
    demandes_administratives.h \
    detention.h \
    equipements.h \
    excel.h \
    login.h \
    mailing/SmtpMime \
    mailing/emailaddress.h \
    mailing/mimeattachment.h \
    mailing/mimecontentformatter.h \
    mailing/mimefile.h \
    mailing/mimehtml.h \
    mailing/mimeinlinefile.h \
    mailing/mimemessage.h \
    mailing/mimemultipart.h \
    mailing/mimepart.h \
    mailing/mimetext.h \
    mailing/quotedprintable.h \
    mailing/smtpclient.h \
    mailing/smtpexports.h \
    mainwindow.h \
    missions.h \
    policier.h \
    reparations.h \
    vehicule.h \
    vehicule_modifier_window.h

FORMS += \
    ajout_reparation.ui \
    calculer.ui \
    chart.ui \
    charttype.ui \
    excel.ui \
    login.ui \
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
    images.qrc \
    qml.qrc \
    translation.qrc
RESOURCES += res.qrc


RESOURCES += DarkOrange/darkorange/darkorange.qrc
QT += core gui \
multimedia


QT += quickwidgets
QT += positioning
QT += location
QT += qml

QMAKE_CXXFLAGS += -std=gnu++14

RC_ICONS = Police.ico

DISTFILES += \
    Police.png \
    english.qm \
    english.ts \
    map.qml

QMAKE_CXXFLAGS += -std=gnu++14
