#ifndef HISTSALE_H
#define HISTSALE_H

#include <QObject>
#include <QStringListModel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include "db_query.h"
#include <QDebug>

namespace Ui {
class histsale;
}
class histsale : public QWidget
{
    Q_OBJECT
public:
    explicit histsale(QWidget *parent = nullptr);
    ~histsale();
    void sethistsaleList(DB_Query::histsalestruct db_histsalestruct);
private:
        void filterList(const QString &text);
    Ui::histsale *ui;
    QLineEdit *Qsearchhistsale;
    QListView *Qhistsale;
    DB_Query db1;
    DB_Query::histsalestruct db_histsalestruct;
    QStringListModel *c_listModel;
    QPushButton *backButton;
};

#endif // histsale_H
