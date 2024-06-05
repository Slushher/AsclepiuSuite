#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "global.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString temp = "A.P.T.E.K.A "+QString::number(version);
    ui->version_label->setText(temp);
    ui->line_password->setEchoMode(QLineEdit::Password);
    connect(ui->signin_button, &QPushButton::released, this, &MainWindow::handleButton);
    setGradient(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    login = ui->line_login->text();
    password = ui->line_password->text();
    validated = login_sesh.validate(login.toStdString(), password.toStdString());
    if(validated){
        this->hide();
        landingWidget.show();
    }
}

std::string MainWindow::getLogin(){
    return this->login.toStdString();
}

std::string MainWindow::getPassword(){
    return this->password.toStdString();
}

