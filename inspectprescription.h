#ifndef INSPECTPRESCRIPTION_H
#define INSPECTPRESCRIPTION_H

#include <QWidget>
#include <QDebug>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>
#include "db_query.h"

namespace Ui {
class inspectprescription;
}

class inspectprescription : public QWidget
{
    Q_OBJECT
private:
    Ui::inspectprescription *ui;
    QString pesel = "";
    QString code = "";
    bool debug_mode = true;
    //DB_Query prescription_query;
    DB_Query::content_struct prescription_content;
    QListView *QprescriptionData;
    QStringListModel *c_listModel;
    QPushButton *backButton;
public:
    DB_Query prescription_query;
    explicit inspectprescription(QWidget *parent = nullptr);
    bool setPreList(DB_Query::content_struct prescription_content);
    void handleButton();
};

#endif // INSPECTPRESCRIPTION_H
