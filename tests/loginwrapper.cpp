#include "loginwrapper.h"

Q_INVOKABLE bool LoginWrapper::validateLogin(const QString &login, const QString &password) {
    Login loginObject;
    return loginObject.validate(login.toStdString(), password.toStdString());
}

Q_INVOKABLE bool LoginWrapper::validatePrescription(const QString &code, const QString &pesel) {
    inspectprescription prescriptionObject;
    DB_Query prescription_query;
    DB_Query::content_struct prescription_content;
    if(debug_mode){
        qDebug() << "TESTING FOR CODE : " << code << "PESEL : " << pesel << "\n";
    }
    prescription_content = prescription_query.prescription_query(code.toStdString(), pesel.toStdString());
    return prescriptionObject.setPreList(prescription_content);
}

Q_INVOKABLE bool LoginWrapper::validateLoginGUI(const QString &login, const QString &password){
    MainWindow w(nullptr);
    if(debug_mode){
        w.setWindowTitle("_floating_ A.P.T.E.K.A [TEST]");
        w.show();
    }
    QLineEdit* usernameField = w.findChild<QLineEdit*>("line_login");
    QLineEdit* passwordField = w.findChild<QLineEdit*>("line_password");
    QPushButton* loginButton = w.findChild<QPushButton*>("signin_button");
    if (usernameField && passwordField && loginButton) {
            QTest::keyClicks(usernameField, login);
            QTest::keyClicks(passwordField, password);
            QTest::mouseClick(loginButton, Qt::LeftButton);
            if (!w.validated) {
                //qDebug() << "UI created succesfully but couldnt login!\n";
                return false;
            }
            else if(w.validated){
                return true;
            }
            //qDebug() << "Succesful login!\n";
        } else {
            //qDebug() << "One or more UI elements could not be found";
            return false;
        }

    return false;
}

Q_INVOKABLE bool LoginWrapper::validatePrescriptionGUI(const QString &code, const QString &pesel){
    bool valid = false;
    inspectprescription w(nullptr);
    if(debug_mode){
        w.setWindowTitle("_floating_ A.P.T.E.K.A [TEST]");
        w.show();
    }
    QLineEdit* peselField = w.findChild<QLineEdit*>("line_pesel");
    QLineEdit* passwordField = w.findChild<QLineEdit*>("line_code");
    QPushButton* loginButton = w.findChild<QPushButton*>("submit");
    if (peselField && passwordField && loginButton) {
            QTest::keyClicks(peselField, code);
            QTest::keyClicks(passwordField, pesel);
            QTest::mouseClick(loginButton, Qt::LeftButton);
            DB_Query::content_struct prescription_content = w.prescription_query.prescription_query(peselField->text().toStdString(), passwordField->text().toStdString());
            valid = w.setPreList(prescription_content);
            if (!valid) {
                //qDebug() << "UI created succesfully but couldnt login!\n";
                return false;
            }
            else if(valid){
                return true;
            }
            //qDebug() << "Succesful login!\n";
        } else {
            //qDebug() << "One or more UI elements could not be found";
            return false;
        }

    return false;
}

void LoginWrapper::printStatus(bool valid, int i, bool expected){
    if(valid == expected){
        qDebug() << "TEST " << i << " [SUCCESS]\n";
    }
    else{
        qDebug() << "TEST " << i << " [FAIL]\n";
    }
}

// NOT A REAL DATA

bool LoginWrapper::testLogin(){
    bool result = true;
    qDebug() << "TESTING : LOGIN MODULE\n";
    bool valid = false;
    valid = validateLogin("test", "1123");
    printStatus(valid, 1, false);
    if(valid){
        result = false;
        qDebug() << "RESULT " << result <<"\n";
    }
    valid = validateLogin("1111", "1111");
    printStatus(valid, 2, false);
    if(valid){
        result = false;
        qDebug() << "RESULT " << result <<"\n";
    }
    valid = validateLogin("test", "1234");
    printStatus(valid, 3, true);
    if(!valid){
        result = false;
        qDebug() << "RESULT " << result <<"\n";
    }
    return result;
}

// NOT A REAL DATA

bool LoginWrapper::testLoginGUI(){
    bool result = true;
    qDebug() << "TESTING : LOGIN GUI MODULE\n";
    bool valid = false;
    valid = validateLoginGUI("test", "1123");
    printStatus(valid, 1, false);
    if(valid){
        result = false;
        qDebug() << "RESULT " << result <<"\n";
    }
    valid = validateLoginGUI("1111", "1111");
    printStatus(valid, 2, false);
    if(valid){
        result = false;
        qDebug() << "RESULT " << result <<"\n";
    }
    valid = validateLoginGUI("test", "1234");
    printStatus(valid, 3, true);
    if(!valid){
        result = false;
        qDebug() << "RESULT " << result <<"\n";
    }
    return result;
}

// NOT A REAL DATA

bool LoginWrapper::testPrescription(){
    bool result = true;
    qDebug() << "TESTING : PRESCRIPTION MODULE\n";
    bool valid = false;
    valid = validatePrescription("1111", "10121230121");
    printStatus(valid, 1, true);
    if(!valid)
        result = false;
    valid = validatePrescription("10121230121", "10121230121");
    printStatus(valid, 2, false);
    if(valid)
        result = false;
    valid = validatePrescription("2222", "10128345211");
    printStatus(valid, 3, true);
    if(!valid)
        result = false;
    return result;
}

bool LoginWrapper::testPrescriptionGUI(){
    bool result = true;
    qDebug() << "TESTING : PRESCRIPTION GUI MODULE\n";
    bool valid = false;
    valid = validatePrescriptionGUI("1111", "10121230121");
    printStatus(valid, 1, true);
    if(!valid)
        result = false;
    valid = validatePrescriptionGUI("10121230121", "10121230121");
    printStatus(valid, 2, false);
    if(valid)
        result = false;
    valid = validatePrescriptionGUI("2222", "10128345211");
    printStatus(valid, 3, true);
    if(!valid)
        result = false;
    return result;
}
