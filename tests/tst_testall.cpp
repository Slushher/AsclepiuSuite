#include <QtTest>
#include <QCoreApplication>
#include "loginwrapper.h"

// add necessary includes here

class testall : public QObject
{
    Q_OBJECT

public:
    testall();
    ~testall();

private slots:
    void initTestCase();
    void test_login();
    void test_prescription();
private:
    LoginWrapper loginwrapper;
    int argc;
    char *argv[2];
    QApplication *a;
};

testall::testall() : argc(1), argv{"testapp", nullptr}
{
    a = new QApplication(argc, argv);
}

testall::~testall()
{

}

void testall::initTestCase()
{
    testall();
}

void testall::test_login()
{
    QVERIFY2(loginwrapper.testLogin(), "LOGIN MODULE TEST [FAIL]");
    QVERIFY2(loginwrapper.testLoginGUI(), "LOGIN GUI TEST [FAIL]");
}

void testall::test_prescription()
{
    QVERIFY2(loginwrapper.testPrescription(), "PRESCRIPTION MODULE TEST [FAIL]");
    QVERIFY2(loginwrapper.testPrescriptionGUI(), "PRESCRIPTION GUI MODULE TEST [FAIL]");
}

QTEST_MAIN(testall)

#include "tst_testall.moc"
