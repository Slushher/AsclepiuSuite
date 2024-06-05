#include "druglist.h"
#include "ui_druglist.h"
#include "global.h"
#include <vector>

druglist::druglist(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::druglist)
{
    ui->setupUi(this);
    c_listModel = new QStringListModel(this);
    Qsearchdrug = ui->Qsearchdrug;
    Qdruglist = ui->Qdruglist;
    refreshMeds();
    setGradient(this);
    connect(Qsearchdrug, &QLineEdit::textChanged, this, &druglist::filterList);
    connect(Qsearchdrug, &QLineEdit::textEdited, this, &druglist::filterList);
    backButton = ui->backButton;
    connect(backButton, &QPushButton::clicked, this, [=]() { goBack(this); });
}

druglist::~druglist()
{
    delete ui;
}

void druglist::refreshMeds()
{
    db_medstruct = db1.meds_return();
    setMedList(db_medstruct);
}

void druglist::filterList(const QString &text) {
    setMedList(db_medstruct);
    QStringListModel *listModel = qobject_cast<QStringListModel*>(Qdruglist->model());
    if (!listModel) {
        return;
    }

    if (text.isEmpty()) {
        Qdruglist->setModel(c_listModel);
        setMedList(db_medstruct);
        return;
    }

    QStringList listSearchResult;
    for (const QString &item : c_listModel->stringList()) {
        if (item.contains(text, Qt::CaseInsensitive)) {
            listSearchResult << item;
        }
    }

    listModel->setStringList(listSearchResult);
}

void druglist::setMedList(DB_Query::medstruct db_medstruct)
{
    QStringList stringList;
    stringList.clear();
    for(size_t i = 0; i < db_medstruct.id.size(); ++i){
        stringList<<QString::fromStdString("'" + db_medstruct.med_name[i]+"', "+QString::number(db_medstruct.dose[i], 'f', 2).toStdString()+"mg"+", "+
                                           std::to_string(db_medstruct.pill_quantity[i])+"szt. " + " x" + std::to_string(db_medstruct.boxes[i])+ ", "+"(EXP): "+
                                           db_medstruct.expiration_date[i] + ", " + QString::number(db_medstruct.price[i], 'f', 2).toStdString()+"zl" + ", " + db_medstruct.active_ingredient[i]);
    }
    c_listModel->setStringList(stringList);
    ui->Qdruglist->setModel(c_listModel);
}
