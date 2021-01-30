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
#include "liftmanagercontroller.h"

#include "liftmanagerworker.h"

LiftManagerController::LiftManagerController(int floorsCount, int liftCapacity,
                                             QObject *parent)
    : QObject(parent), mFloorsCount{floorsCount}, mLiftCapacity{liftCapacity}
{
    auto liftManagerWorker = new LiftManagerWorker{mFloorsCount, mLiftCapacity};
    liftManagerWorker->moveToThread(&mWorkerThread);
    connect(&mWorkerThread, &QThread::finished, liftManagerWorker,
            &QObject::deleteLater);
    connect(this, &LiftManagerController::startLift, liftManagerWorker,
            &LiftManagerWorker::runLift);

    // "getter signals"
    connect(liftManagerWorker, &LiftManagerWorker::liftLevelChanged, this,
            &LiftManagerController::liftLevelChanged);
    connect(liftManagerWorker, &LiftManagerWorker::liftCapacityChanged, this,
            &LiftManagerController::liftCapacityChanged);
    connect(liftManagerWorker, &LiftManagerWorker::peopleOnFloorChanged, this,
            &LiftManagerController::peopleOnFloorChanged);
    connect(liftManagerWorker, &LiftManagerWorker::peopleInLiftChanged, this,
            &LiftManagerController::peopleInLiftChanged);

    // "setter signals"
    connect(this, &LiftManagerController::changeLiftCapacity, liftManagerWorker,
            &LiftManagerWorker::changeLiftCapacity);

    mWorkerThread.start();
}

LiftManagerController::~LiftManagerController()
{
    mWorkerThread.quit();
    mWorkerThread.wait();
}

void LiftManagerController::start()
{
    emit startLift();
}

int LiftManagerController::floorsCount() const
{
    return mFloorsCount;
}

int LiftManagerController::liftCapacity() const
{
    return mLiftCapacity;
}
