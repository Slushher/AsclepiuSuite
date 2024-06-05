#ifndef HISTORDER_H
#define HISTORDER_H

#include <QObject>
#include <QStringListModel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include "db_query.h"
#include <QDebug>

namespace Ui {
class historder;
}
class historder : public QWidget
{
    Q_OBJECT
public:
    explicit historder(QWidget *parent = nullptr);
    ~historder();
    void sethistList(DB_Query::historderstruct db_historderstruct);
private:
        void filterList(const QString &text);
    Ui::historder *ui;
    QLineEdit *Qsearchhist;
    QListView *Qhistorder;
    DB_Query db1;
    DB_Query::historderstruct db_historderstruct;
    QStringListModel *c_listModel;
    QPushButton *backButton;
};

#endif // HISTORDER_H
