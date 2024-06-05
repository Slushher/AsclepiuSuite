#include "landing.h"
#include "ui_landing.h"
#include "global.h"

landing::landing(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::landing)
{
    ui->setupUi(this);
    setGradient(this);
    for (int i = 1; i <= 6; ++i) {
        QPushButton *button = findChild<QPushButton*>(QString("pushButton_%1").arg(i));
        if (button) {
            connect(button, &QPushButton::clicked, this, &landing::on_pushButtonClicked);
        }
    }
    this->setWindowTitle("_floating_ A.P.T.E.K.A");
    inspectWidget.setWindowTitle("_floating_ A.P.T.E.K.A");
    dsWidget.setWindowTitle("_floating_ A.P.T.E.K.A");
}

void landing::on_pushButtonClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        QString buttonText = clickedButton->objectName().remove(0, 11);
        int buttonNumber = buttonText.toInt();
        if(debug_mode){
            qDebug() << "button" << buttonNumber << "pressed";
        }
        emit switchToWidget(buttonNumber);
    }
}

void landing::switchToWidget(int widgetType)
{
    dsWidget.hide();
    inspectWidget.hide();
    retailWidget.hide();
    orderWidget.hide();
    historyWidget.hide();
    histsaleWidget.hide();
    switch (widgetType) {
    case 1:
        orderWidget.show();
        break;
    case 2:
        inspectWidget.show();
        break;
    case 3:
        dsWidget.show();
        dsWidget.refreshMeds();
        break;
    case 4:
        retailWidget.show();
        retailWidget.refreshMeds();
        break;
    case 5:
        historyWidget.show();
        break;
    case 6:
        histsaleWidget.show();
        break;
    default:
        break;
    }
}

landing::~landing()
{
    delete ui;
}
