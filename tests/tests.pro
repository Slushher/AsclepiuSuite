QT += testlib core widgets
QT += gui
CONFIG += qt warn_on depend_includepath testcase c++17

TEMPLATE = app

INCLUDEPATH += "/home/dd/A.P.T.E.K.A/Desktop2/tests/include/jdbc"
INCLUDEPATH += "/home/dd/A.P.T.E.K.A/Desktop2/tests/include/jdbc/cppconn"
INCLUDEPATH += "/usr/include/x86_64-linux-gnu/qt5"

LIBS += -L/usr/lib64 -lmysqlcppconn
LIBS += -L/usr/lib64 -lmysqlclient

SOURCES +=  tst_testall.cpp \
    loginwrapper.cpp \
    ../login.cpp \
    ../inspectprescription.cpp \
    ../db_query.cpp \
    ../mainwindow.cpp \
    ../druglist.cpp \
    ../historder.cpp \
    ../histsale.cpp \
    ../landing.cpp \
    ../order.cpp \
    ../retail.cpp

HEADERS += \
    loginwrapper.h \
    ../login.h \
    ../inspectprescription.h \
    ../db_query.h \
    ../mainwindow.h \
    ../druglist.h \
    ../global.h \
    ../historder.h \
    ../histsale.h \
    ../landing.h \
    ../order.h \
    ../retail.h

INCLUDEPATH += \
    ../ \
    /home/dd/A.P.T.E.K.A/build-Webapp-Desktop-Debug
