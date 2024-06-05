#include "historder.h"
#include "ui_historder.h"
#include "global.h"

historder::historder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historder)

{
    ui->setupUi(this);
    c_listModel = new QStringListModel(this);
    Qsearchhist = ui->Qsearchhist;
    Qhistorder = ui->Qhistorder;

    db_historderstruct = db1.history_query();
    sethistList(db_historderstruct);
    setGradient(this);
    connect(Qsearchhist, &QLineEdit::textChanged, this, &historder::filterList);
    connect(Qsearchhist, &QLineEdit::textEdited, this, &historder::filterList);
    backButton = ui->backButton;
    connect(backButton, &QPushButton::clicked, this, [=]() { goBack(this); });
}

 historder::~historder()
 {
     delete ui;
 }

 void historder::filterList(const QString &text) {
     sethistList(db_historderstruct);
     QStringListModel *listModel = qobject_cast<QStringListModel*>(Qhistorder->model());
     if (!listModel) {
         return;
     }

     if (text.isEmpty()) {
         Qhistorder->setModel(c_listModel);
         sethistList(db_historderstruct);
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

 void historder::sethistList(DB_Query::historderstruct db_historderstruct)
 {
     QStringList stringList;
     for(size_t i = 0; i < db_historderstruct.id.size(); ++i){
         stringList<<QString::fromStdString(std::to_string(db_historderstruct.id[i])+" "+db_historderstruct.med_name[i]+" "+QString::number(db_historderstruct.boxes[i]).toStdString()+" "+QString::number(db_historderstruct.dose[i], 'f', 2).toStdString());
     }
     c_listModel->setStringList(stringList);
     ui->Qhistorder->setModel(c_listModel);
 }
