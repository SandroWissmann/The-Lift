#include <QCoreApplication>
#include <QtTest>

#include "../TheLift/lift.h"

class Lift_test : public QObject {
    Q_OBJECT

public:
    Lift_test();
    ~Lift_test();

private slots:
    void test_getFloors_data();
    void test_getFloors();
};

Lift_test::Lift_test()
{
}

Lift_test::~Lift_test()
{
}

void Lift_test::test_getFloors_data()
{
    QTest::addColumn<std::vector<std::vector<int>>>("queues");
    QTest::addColumn<int>("capacity");
    QTest::addColumn<std::vector<int>>("expectedFloorsVisited");

    QTest::newRow("nothing to do")
        << std::vector<std::vector<int>>{{}} << 1 << std::vector<int>{0};
    QTest::newRow("lift full up and down, but don't block passengers")
        << std::vector<std::vector<int>>{{},
                                         {3, 3, 3, 0, 0, 0, 0, 0, 3},
                                         {},
                                         {1, 1, 1}}
        << 2 << std::vector<int>{0, 1, 3, 1, 0, 1, 3, 1, 0, 1, 0};
    QTest::newRow("lift exactly full")
        << std::vector<std::vector<int>>{{}, {}, {5, 5, 5, 5, 5}, {}, {},
                                         {}, {}}
        << 5 << std::vector<int>{0, 2, 5, 0};
    QTest::newRow("up") << std::vector<std::vector<int>>{{}, {}, {5, 5, 5}, {},
                                                         {}, {}, {}}
                        << 5 << std::vector<int>{0, 2, 5, 0};
    QTest::newRow("down") << std::vector<std::vector<int>>{{}, {}, {1, 1}, {},
                                                           {}, {}, {}}
                          << 5 << std::vector<int>{0, 2, 1, 0};
    QTest::newRow("up and up")
        << std::vector<std::vector<int>>{{}, {3}, {4}, {}, {5}, {}, {}} << 5
        << std::vector<int>{0, 1, 2, 3, 4, 5, 0};
    QTest::newRow("down and down")
        << std::vector<std::vector<int>>{{}, {0}, {}, {}, {2}, {3}, {}} << 5
        << std::vector<int>{0, 5, 4, 3, 2, 1, 0};
    QTest::newRow("yoyo")
        << std::vector<std::vector<int>>{{}, {}, {4, 4, 4, 4}, {}, {2, 2, 2, 2},
                                         {}, {}}
        << 2 << std::vector<int>{0, 2, 4, 2, 4, 2, 0};
    QTest::newRow("lift full up")
        << std::vector<std::vector<int>>{{3, 3, 3, 3, 3, 3},
                                         {},
                                         {},
                                         {},
                                         {},
                                         {},
                                         {}}
        << 5 << std::vector<int>{0, 3, 0, 3, 0};
    QTest::newRow("lift full down")
        << std::vector<std::vector<int>>{{}, {},
                                         {}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                         {}, {},
                                         {}}
        << 5 << std::vector<int>{0, 3, 1, 3, 1, 3, 1, 0};
    QTest::newRow("lift full up and down")
        << std::vector<std::vector<int>>{{3, 3, 3, 3, 3, 3}, {}, {}, {}, {},
                                         {4, 4, 4, 4, 4, 4}, {}}
        << 5 << std::vector<int>{0, 3, 5, 4, 0, 3, 5, 4, 0};
    QTest::newRow("tricky queues")
        << std::vector<std::vector<int>>{{}, {0, 0, 0, 6},       {}, {},
                                         {}, {6, 6, 0, 0, 0, 6}, {}}
        << 5 << std::vector<int>{0, 1, 5, 6, 5, 1, 0, 1, 0};
    QTest::newRow("highlander")
        << std::vector<std::vector<int>>{{}, {2}, {3, 3, 3}, {1}, {}, {}, {}}
        << 1 << std::vector<int>{0, 1, 2, 3, 1, 2, 3, 2, 3, 0};
    QTest::newRow("fire drill")
        << std::vector<std::vector<int>>{{},           {0, 0, 0, 0},
                                         {0, 0, 0, 0}, {0, 0, 0, 0},
                                         {0, 0, 0, 0}, {0, 0, 0, 0},
                                         {0, 0, 0, 0}}
        << 5 << std::vector<int>{0, 6, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1,
                                 0, 4, 3, 2, 1, 0, 3, 2, 1, 0, 1, 0};
    QTest::newRow("no floors (seg fault)")
        << std::vector<std::vector<int>>{} << 1 << std::vector<int>{0};
    QTest::newRow("no capacity")
        << std::vector<std::vector<int>>{{1}, {}} << 0 << std::vector<int>{0};
    QTest::newRow("passenger not changing floor (infinite loop)")
        << std::vector<std::vector<int>>{{0}} << 1 << std::vector<int>{0};
}

void Lift_test::test_getFloors()
{
    QFETCH(std::vector<std::vector<int>>, queues);
    QFETCH(int, capacity);
    QFETCH(std::vector<int>, expectedFloorsVisited);

    Lift lift(queues, capacity);
    //    lift.emptyQueues();
    //    QCOMPARE(lift.visitedFloors(), expectedFloorsVisited);
}

QTEST_APPLESS_MAIN(Lift_test)

#include "tst_lift_test.moc"