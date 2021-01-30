/* The Lift
 * Copyright (C) 2021  Sandro Wißmann
 *
 * The Lift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Lift is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The Lift If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/The-Lift
 */
#include <QCoreApplication>
#include <QtTest>

#include "../TheLift/building.h"
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
    QTest::addColumn<QVector<QVector<int>>>("queues");
    QTest::addColumn<int>("capacity");
    QTest::addColumn<QVector<int>>("expectedFloorsVisited");

    QTest::newRow("nothing to do")
        << QVector<QVector<int>>{{}} << 1 << QVector<int>{0};
    QTest::newRow("lift full up and down, but don't block passengers")
        << QVector<QVector<int>>{{}, {3, 3, 3, 0, 0, 0, 0, 0, 3}, {}, {1, 1, 1}}
        << 2 << QVector<int>{0, 1, 3, 1, 0, 1, 3, 1, 0, 1, 0};
    QTest::newRow("lift exactly full")
        << QVector<QVector<int>>{{}, {}, {5, 5, 5, 5, 5}, {}, {}, {}, {}} << 5
        << QVector<int>{0, 2, 5, 0};
    QTest::newRow("up") << QVector<QVector<int>>{{}, {}, {5, 5, 5}, {},
                                                 {}, {}, {}}
                        << 5 << QVector<int>{0, 2, 5, 0};
    QTest::newRow("down") << QVector<QVector<int>>{{}, {}, {1, 1}, {},
                                                   {}, {}, {}}
                          << 5 << QVector<int>{0, 2, 1, 0};
    QTest::newRow("up and up")
        << QVector<QVector<int>>{{}, {3}, {4}, {}, {5}, {}, {}} << 5
        << QVector<int>{0, 1, 2, 3, 4, 5, 0};
    QTest::newRow("down and down")
        << QVector<QVector<int>>{{}, {0}, {}, {}, {2}, {3}, {}} << 5
        << QVector<int>{0, 5, 4, 3, 2, 1, 0};
    QTest::newRow("yoyo")
        << QVector<QVector<int>>{{}, {}, {4, 4, 4, 4}, {}, {2, 2, 2, 2}, {}, {}}
        << 2 << QVector<int>{0, 2, 4, 2, 4, 2, 0};
    QTest::newRow("lift full up")
        << QVector<QVector<int>>{{3, 3, 3, 3, 3, 3}, {}, {}, {}, {}, {}, {}}
        << 5 << QVector<int>{0, 3, 0, 3, 0};
    QTest::newRow("lift full down")
        << QVector<QVector<int>>{{}, {}, {}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {}, {}, {}}
        << 5 << QVector<int>{0, 3, 1, 3, 1, 3, 1, 0};
    QTest::newRow("lift full up and down")
        << QVector<QVector<int>>{{3, 3, 3, 3, 3, 3}, {}, {}, {}, {},
                                 {4, 4, 4, 4, 4, 4}, {}}
        << 5 << QVector<int>{0, 3, 5, 4, 0, 3, 5, 4, 0};
    QTest::newRow("tricky queues")
        << QVector<QVector<int>>{{}, {0, 0, 0, 6},       {}, {},
                                 {}, {6, 6, 0, 0, 0, 6}, {}}
        << 5 << QVector<int>{0, 1, 5, 6, 5, 1, 0, 1, 0};
    QTest::newRow("highlander")
        << QVector<QVector<int>>{{}, {2}, {3, 3, 3}, {1}, {}, {}, {}} << 1
        << QVector<int>{0, 1, 2, 3, 1, 2, 3, 2, 3, 0};
    QTest::newRow("fire drill")
        << QVector<QVector<int>>{{},           {0, 0, 0, 0}, {0, 0, 0, 0},
                                 {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
                                 {0, 0, 0, 0}}
        << 5 << QVector<int>{0, 6, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1,
                             0, 4, 3, 2, 1, 0, 3, 2, 1, 0, 1, 0};
}

void Lift_test::test_getFloors()
{
    QFETCH(QVector<QVector<int>>, queues);
    QFETCH(int, capacity);
    QFETCH(QVector<int>, expectedFloorsVisited);

    Building *building = new Building(queues);
    Lift lift(building, capacity);

    QVector<int> visitedFloors;
    visitedFloors.push_back(lift.currentFloor());
    while (!(building->allQueuesEmpty() && !lift.hasPassengers() &&
             lift.currentFloor() == 0)) {
        lift.goToNextFloor();
        visitedFloors.push_back(lift.currentFloor());
    }
    QCOMPARE(visitedFloors, expectedFloorsVisited);
}

QTEST_APPLESS_MAIN(Lift_test)

#include "tst_lift_test.moc"
