#ifndef DRUGLIST_H
#define DRUGLIST_H

#include <QWidget>
#include <QStringListModel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include "db_query.h"
#include <QDebug>

namespace Ui {
class druglist;
}

class druglist : public QWidget
{
    Q_OBJECT

public:
    explicit druglist(QWidget *parent = nullptr);
    ~druglist();
    void setMedList(DB_Query::medstruct db_medstruct);
    void refreshMeds();
private:
    void filterList(const QString &text);
    Ui::druglist *ui;
    QLineEdit *Qsearchdrug;
    QListView *Qdruglist;
    DB_Query db1;
    DB_Query::medstruct db_medstruct;
    QStringListModel *c_listModel;
    QPushButton *backButton;
};

#endif // DRUGLIST_H
