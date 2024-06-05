#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include <QUrl>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QString>
#include "db_query.h"

namespace Ui {
class order;
}

class order : public QWidget
{
    Q_OBJECT

public:
    explicit order(QWidget *parent = nullptr);
    ~order();
    bool orderMeds();

private:
    Ui::order *ui;
    QVBoxLayout *layout;
    //QWidget *orderWidget;
    QPushButton *backButton;
    QPushButton *orderButton;
    DB_Query med_query;
};

#endif // ORDER_H
