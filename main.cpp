#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include "./ui_mainwindow.h"

#include "landing.h"
#include <iostream>
#include <vector>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    landing ladingWidget(nullptr);
    w.setWindowTitle("_floating_ A.P.T.E.K.A");
    ladingWidget.setWindowTitle("_floating_ A.P.T.E.K.A");
    w.show();
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&w, &ladingWidget]() {
        QCoreApplication::processEvents();
    });

    timer.start(100);
    return a.exec();
}
