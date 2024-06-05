#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "db_query.h"
#include "login.h"
#include "landing.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string getLogin();
    std::string getPassword();
    bool validated = false;
    void switchToWidgetSlot(int widgetType);
private:
    //DrugScreen *drugScreen;
    void handleButton();
    const float version = 0.1;
    QString login = "";
    QString password = "";
    Ui::MainWindow *ui;
    Login login_sesh;
    landing landingWidget;
};
#endif // MAINWINDOW_H
