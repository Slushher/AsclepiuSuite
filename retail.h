#ifndef RETAIL_H
#define RETAIL_H

#include <QWidget>
#include <QPushButton>
#include <QStringListModel>
#include <QListView>
#include <QLineEdit>
#include <regex>
#include <string>
#include "db_query.h"

namespace Ui {
class retail;
}

class retail : public QWidget
{
    Q_OBJECT

public:
    explicit retail(QWidget *parent = nullptr);
    ~retail();
    void setMedList(DB_Query::medstruct db_medstruct);
    void setCartList(DB_Query::medstruct db_medcart);
    void refreshMeds();
private:
    void filterList(const QString &text);
    void addItemToCart();
    void removeItemFromCart();
    void resetTransaction();
    void checkoutCart();
    double castToDouble(std::string num);
    Ui::retail *ui;
    QLineEdit *Qsearchdrug;
    QListView *Qdruglist;
    QListView *Qcartlist;
    DB_Query db1;
    DB_Query::medstruct db_medstruct;
    DB_Query::medstruct db_medstruct_original;
    DB_Query::medstruct db_medcart;
    QStringListModel *c_listModel;
    QStringListModel *c_cartModel;
    QPushButton *backButton;
    QPushButton *Qaddcart;
    QPushButton *Qclearcart;
    QPushButton *Qproceed;
    QPushButton *Qdropcart;
    std::vector<std::regex> rx = {std::regex("'(.*?)'"),          // med_name
                                  std::regex("(\\d+\\.\\d+)mg"),  // dose
                                  std::regex("(\\d+)szt\\."),     // pills
                                  std::regex("x(\\d+)"),          // boxes
                                  std::regex("(\\d+\\.\\d+)zl")   // price
                                 };

};

#endif // RETAIL_H
