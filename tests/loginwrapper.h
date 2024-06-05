#pragma once

#include <QObject>
#include <QDebug>
#include <QtTest/QtTest>
#include <QLineEdit>
#include <QPushButton>
#include "login.h"
#include "inspectprescription.h"
#include "db_query.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

class LoginWrapper : public QObject {
    Q_OBJECT
    bool debug_mode = false;
public:
    Q_INVOKABLE bool validateLogin(const QString &login, const QString &password);
    Q_INVOKABLE bool validatePrescription(const QString &code, const QString &pesel);
    Q_INVOKABLE bool validateLoginGUI(const QString &login, const QString &password);
    Q_INVOKABLE bool validatePrescriptionGUI(const QString &code, const QString &pesel);
    void printStatus(bool valid, int i, bool expected);
    bool testLogin();
    bool testLoginGUI();
    bool testPrescription();
    bool testPrescriptionGUI();
};
