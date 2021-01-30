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
#ifndef LIFT_H
#define LIFT_H

#include <QObject>
#include <QVector>

#include <optional>
#include <set>

class Building;

class Lift : public QObject {
    Q_OBJECT
public:
    Lift(Building *building, int capacity, unsigned long delayOpenDoors = 500,
         QObject *parent = nullptr);

    bool hasPassengers() const;
    int currentFloor() const;

public slots:
    void setCapacity(int capacity);

public:
    int capacity() const;

    enum class Direction { up, down };

    void goToNextFloor();

    QString passengersAsString();
signals:
    void arrivedToNewFloor(int floor);
    void passengersChanged(const QString &passengers);
    void capacityChanged(int capacity);

private:
    void releasePassengersWithCurrentFloorDestination();

    bool goUp();

    void addPeopleWhoWantToGoUp();

    bool goUpWithoutPassengers();

    bool goUpToNextFloorPushedUp();
    bool goUpToHighestFloorPushedDown();

    void goUpWithPassengers();

    int getNextFloorUpWithPerson() const;

    bool goDown();

    void addPeopleWhoWantToGoDown();

    bool goDownWithoutPassengers();

    bool goDownToNextFloorPushedDown();
    bool goDownToLowestFloorPushedUp();

    void goDownWithPassengers();

    int getNextFloorDownWithPerson() const;

    void arriveToFloor(int floor);

    void changeDirection();
    Direction direction() const;

    std::multiset<int> mPassengers{};
    Direction mDirection = Direction::up;
    int mCurrentFloor = 0;
    int mCapacity;
    const unsigned long mDelayOpenDoors;

    Building *mBuilding;
};

#endif // LIFT_H
