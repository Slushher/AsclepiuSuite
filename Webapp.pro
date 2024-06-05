QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets testlib

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "include/jdbc"
INCLUDEPATH += "include/jdbc/cppconn"
INCLUDEPATH += "/usr/include/x86_64-linux-gnu/qt5"

LIBS += -L/usr/lib64 -lmysqlcppconn
LIBS += -L/usr/lib64 -lmysqlclient

SOURCES += \
    db_query.cpp \
    druglist.cpp \
    historder.cpp \
    histsale.cpp \
    inspectprescription.cpp \
    landing.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp \
    retail.cpp

HEADERS += \
    db_query.h \
    druglist.h \
    global.h \
    historder.h \
    histsale.h \
    inspectprescription.h \
    landing.h \
    login.h \
    mainwindow.h \
    order.h \
    retail.h

FORMS += \
    druglist.ui \
    historder.ui \
    histsale.ui \
    homescreen.ui \
    inspectprescription.ui \
    landing.ui \
    login.ui \
    mainwindow.ui \
    order.ui \
    retail.ui

TRANSLATIONS += \
    Webapp_pl_PL.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    tests/main_test_.qml \
    tests/tst_loginwrapper.qml \
    tst_loginwrapper.qml \
    tst_main_test_.qml
