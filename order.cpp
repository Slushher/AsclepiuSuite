#include "order.h"
#include "ui_order.h"
#include "global.h"

order::order(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::order)
{
    ui->setupUi(this);
    setGradient(this);
    this->setWindowTitle("_floating_ A.P.T.E.K.A");
    backButton = ui->backButton;
    connect(backButton, &QPushButton::clicked, this, [=]() { goBack(this); });
    orderButton = ui->orderButton;
    connect(orderButton, &QPushButton::clicked, this, [=]() { orderMeds(); });
}

order::~order()
{
    delete ui;
}

bool order::orderMeds()
{
    DB_Query::medstruct fuck1;
    fuck1.clear();
    DB_Query::medstruct history;
    history.clear();

    QString drugname = ui->drugnameLine->text();
    QString tabquantity = ui->tabquantityLine->text();
    QString dose = ui->doseLine->text();
    QString boxes = ui->boxesLine->text();
    QString price = ui->priceLine->text();
    QString substance = ui->substanceLine->text();

    QDateTime currentDate = QDateTime::currentDateTime();
    QString dateStr = currentDate.toString("yyyy-MM-dd");
    //qDebug() << "EXPIRATION DATE before 3 year : " << dateStr << "\n";

    QDateTime expirationDate = currentDate.addYears(3);
    QString expirationDateStr = expirationDate.toString("yyyy-MM-dd");
    //qDebug() << "EXPIRATION DATE : " << expirationDateStr << "\n";

    fuck1.med_name.push_back(drugname.toStdString());
    fuck1.pill_quantity.push_back(tabquantity.toInt());
    fuck1.dose.push_back(dose.toDouble());
    fuck1.boxes.push_back(boxes.toInt());
    fuck1.expiration_date.push_back(expirationDateStr.toStdString());
    fuck1.price.push_back(price.toDouble());
    fuck1.active_ingredient.push_back(substance.toStdString());

    history.med_name.push_back(drugname.toStdString());
    history.pill_quantity.push_back(tabquantity.toInt());
    history.boxes.push_back(boxes.toInt());
    history.dose.push_back(dose.toDouble());
    history.price.push_back(price.toDouble());
    history.expiration_date.push_back(dateStr.toStdString());
    med_query.meds_order(fuck1);
    med_query.history_add(history, 0);
    return false;
}
