#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class Lift : public QObject
{
    Q_OBJECT

public:
    Lift();
    ~Lift();

private slots:
    void test_case1();

};

Lift::Lift()
{

}

Lift::~Lift()
{

}

void Lift::test_case1()
{

}

QTEST_MAIN(Lift)

#include "tst_lift.moc"
