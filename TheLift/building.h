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
#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QVector>

class Building : public QObject {
    Q_OBJECT
public:
    explicit Building(const QVector<QVector<int>> &queues,
                      QObject *parent = nullptr);

    explicit Building(int floorsCount, QObject *parent = nullptr);

    void sendAllPeopleRequestingLift();

    bool allQueuesEmpty() const;

    std::optional<int> highestFloorAboveLiftPushedDown(int liftPos) const;

    std::optional<int> nextFloorAboveLiftPushedUp(int liftPos) const;

    std::optional<int> nextFloorUnderLiftPushedDown(int liftPos) const;

    std::optional<int> lowestFloorUnderLiftPushedUp(int liftPos) const;

    QVector<int> peopleOnFloorWaiting(int floor) const;

    QVector<int> removePeopleWhoWantToGoDown(int maxSize, int floor);

    QVector<int> removePeopleWhoWantToGoUp(int maxSize, int floor);

    int floorsCount() const;

public slots:
    void addPersonWaitingForLift(int personWaitingForLift, int floor);
    void addPersonWaitingForLift(const QVector<int> &personsWaitingForLift,
                                 int floor);

signals:
    void peopleRequestingLiftChanged(const QVector<int> persons, int floor);
    void noPeopleWaiting();

private:
    QVector<QVector<int>> mQueues;
};

QVector<QVector<int>> makeFloors(int floorsCount);

#endif // BUILDING_H
