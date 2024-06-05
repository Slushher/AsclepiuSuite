#include "inspectprescription.h"
#include "ui_inspectprescription.h"
#include "global.h"

inspectprescription::inspectprescription(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::inspectprescription)
{
    ui->setupUi(this);
    QprescriptionData = ui->QprescriptionData;
    c_listModel = new QStringListModel(this);
    connect(ui->submit, &QPushButton::released, this, &inspectprescription::handleButton);
    setGradient(this);
    backButton = ui->backButton;
    connect(backButton, &QPushButton::clicked, this, [=]() { goBack(this); });
}

void inspectprescription::handleButton()
{
    //prescription_content.clear();
    pesel = ui->line_pesel->text();
    code = ui->line_code->text();
    if(debug_mode){
        qDebug() << "pesel : " << pesel << "code : " << code;
    }
    prescription_content = prescription_query.prescription_query(code.toStdString(), pesel.toStdString());
    setPreList(prescription_content);
}

bool inspectprescription::setPreList(DB_Query::content_struct prescription_content)
{
    QStringList stringList;
    for(size_t i = 0; i < prescription_content.id.size(); ++i){
    stringList<<QString::fromStdString(prescription_content.med_name[i]+" "+
                                           //prescription_content.active_ingredient[i]+" "+
                                           std::to_string(prescription_content.boxes[i])+" "+
                                           std::to_string(prescription_content.pill_quantity[i])+" "+
                                           QString::number(prescription_content.dose[i], 'f', 2).toStdString() +" "+
                                           QString::number(prescription_content.discount[i], 'f', 2).toStdString());
    }
    c_listModel->setStringList(stringList);
    ui->QprescriptionData->setModel(c_listModel);
    if(stringList.isEmpty()){
        qDebug() << "String list empty\n";
        return false;
    }
    return true;
}
