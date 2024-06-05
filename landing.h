#ifndef LANDING_H
#define LANDING_H

#include <QWidget>
#include <QDebug>

#include "druglist.h"
#include "inspectprescription.h"
#include "order.h"
#include "retail.h"
#include "historder.h"
#include "histsale.h"

namespace Ui {
class landing;
}

class landing : public QWidget
{
    Q_OBJECT

public:
    explicit landing(QWidget *parent = nullptr);
    ~landing();
    void on_pushButtonClicked();
signals:

public slots:
    void switchToWidget(int widgetType);
private:
    Ui::landing *ui;
    druglist dsWidget;
    inspectprescription inspectWidget;
    order orderWidget;
    retail retailWidget;
    historder historyWidget;
    histsale histsaleWidget;
    bool debug_mode = false;
};

#endif // LANDING_H
