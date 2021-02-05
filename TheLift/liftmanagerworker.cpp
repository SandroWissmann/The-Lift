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
#include "liftmanagerworker.h"

#include "building.h"
#include "lift.h"

#include <QTimer>

QVector<QVector<int>> queues{{},           {2, 2, 3, 3}, {4, 4, 5, 5},
                             {6, 6, 6, 6}, {1, 1, 2, 2}, {3, 3, 4, 4},
                             {1, 1, 1, 1}};

LiftManagerWorker::LiftManagerWorker(int floorsCount, int liftCapacity,
                                     QObject *parent)
    : QObject(parent), mBuilding{new Building(floorsCount, this)},
      mLift{new Lift(mBuilding, liftCapacity, 500, this)}
{
    // "getter signals"
    connect(mLift, &Lift::arrivedToNewFloor, this,
            &LiftManagerWorker::liftLevelChanged);

    connect(mLift, &Lift::passengersChanged, this,
            &LiftManagerWorker::peopleInLiftChanged);

    connect(mBuilding, &Building::peopleRequestingLiftChanged, this,
            &LiftManagerWorker::peopleOnFloorChanged);

    // "setter signals"
    connect(this, &LiftManagerWorker::changeLiftCapacity, mLift,
            &Lift::setCapacity);

    // remove later
    for (int i = 0; i < queues.size(); ++i) {
        mBuilding->addPersonWaitingForLift(queues[i], i);
    }
}

void LiftManagerWorker::runLift()
{
    emit peopleInLiftChanged(mLift->passengersAsString());
    emit liftLevelChanged(mLift->currentFloor());

    mBuilding->sendAllPeopleRequestingLift();

    QTimer::singleShot(0, this, &LiftManagerWorker::goToNextFloor);
}

void LiftManagerWorker::startLift(bool started)
{
    if (mLiftStarted == started) {
        return;
    }
    mLiftStarted = started;
    runLift();
}

void LiftManagerWorker::goToNextFloor()
{
    if (!mLiftStarted) {
        return;
    }
    mLift->goToNextFloor();
    QTimer::singleShot(2000, this, &LiftManagerWorker::goToNextFloor);
}
