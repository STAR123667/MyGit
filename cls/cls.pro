QT       += core
QT       += gui
QT       += widgets
QT       += charts
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CAN
CONFIG += c++17

#DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ai_python.cpp \
    canthread.cpp \
    configurationmanagement.cpp \
    dataface.cpp \
    datamanagement.cpp \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    manualoperation.cpp \
    mysql.cpp \
    network.cpp \
    pagecontrol.cpp \
    systemmanagement.cpp \
    workmanagement.cpp

HEADERS += \
    ai_python.h \
    canthread.h \
    configurationmanagement.h \
    dataface.h \
    datamanagement.h \
    homepage.h \
    mainwindow.h \
    manualoperation.h \
    mysql.h \
    network.h \
    pagecontrol.h \
    systemmanagement.h \
    workmanagement.h

FORMS += \
    configurationmanagement.ui \
    dataface.ui \
    datamanagement.ui \
    homepage.ui \
    mainwindow.ui \
    manualoperation.ui \
    network.ui \
    pagecontrol.ui \
    systemmanagement.ui \
    workmanagement.ui

TRANSLATIONS += \
    cls_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/./ -lcontrolcan

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/./libcontrolcan.a
