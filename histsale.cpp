#include "histsale.h"
#include "ui_histsale.h"
#include "global.h"

histsale::histsale(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::histsale)

{
    ui->setupUi(this);
    c_listModel = new QStringListModel(this);
    Qsearchhistsale = ui->Qsearchhistsale;
    Qhistsale = ui->Qhistsale;

    db_histsalestruct = db1.histsale_return();
    sethistsaleList(db_histsalestruct);
    setGradient(this);
    connect(Qsearchhistsale, &QLineEdit::textChanged, this, &histsale::filterList);
    connect(Qsearchhistsale, &QLineEdit::textEdited, this, &histsale::filterList);
    backButton = ui->backButton;
    connect(backButton, &QPushButton::clicked, this, [=]() { goBack(this); });
}

 histsale::~histsale()
 {
     delete ui;
 }

 void histsale::filterList(const QString &text) {
     sethistsaleList(db_histsalestruct);
     QStringListModel *listModel = qobject_cast<QStringListModel*>(Qhistsale->model());
     if (!listModel) {
         return;
     }

     if (text.isEmpty()) {
         Qhistsale->setModel(c_listModel);
         sethistsaleList(db_histsalestruct);
         //qDebug() << "listModel: " << listModel;
         return;
     }

     QStringList listSearchResult;
     for (const QString &item : c_listModel->stringList()) {
         if (item.contains(text, Qt::CaseInsensitive)) {
             listSearchResult << item;
             //qDebug() << "listSearchResult: " << listSearchResult;
         }
     }

     listModel->setStringList(listSearchResult);
 }

 void histsale::sethistsaleList(DB_Query::histsalestruct db_histsalestruct)
 {
     QStringList stringList;
     //qDebug() << "size " << db_histsalestruct.id.size();
     for(size_t i = 0; i < db_histsalestruct.id.size(); ++i){
         stringList<<QString::fromStdString(std::to_string(db_histsalestruct.id[i])+" "+db_histsalestruct.med_name[i]+" "+QString::number(db_histsalestruct.boxes[i]).toStdString()+" "+QString::number(db_histsalestruct.dose[i], 'f', 2).toStdString()+" "+db_histsalestruct.order_date[i]+" "+std::to_string(db_histsalestruct.receipt_id[i]));
     }
     c_listModel->setStringList(stringList);
     ui->Qhistsale->setModel(c_listModel);
 }
