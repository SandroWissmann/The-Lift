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
}

void LiftManagerWorker::runLift()
{
    // remove later
    for (int i = 0; i < queues.size(); ++i) {
        mBuilding->addPersonWaitingForLift(queues[i], i);
    }

    emit peopleInLiftChanged(mLift->passengersAsString());
    emit liftLevelChanged(mLift->currentFloor());

    mBuilding->sendAllPeopleRequestingLift();

    QTimer::singleShot(0, this, &LiftManagerWorker::goToNextFloor);
}

void LiftManagerWorker::goToNextFloor()
{
    mLift->goToNextFloor();
    QTimer::singleShot(2000, this, &LiftManagerWorker::goToNextFloor);
}
