#include "liftmanagerworker.h"

#include "building.h"
#include "lift.h"

#include <QTimer>

constexpr int floorCount = 7;
constexpr int capacity = 5;

QVector<QVector<int>> queues{{},           {2, 2, 3, 3}, {4, 4, 5, 5},
                             {6, 6, 6, 6}, {1, 1, 2, 2}, {3, 3, 4, 4},
                             {1, 1, 1, 1}};

LiftManagerWorker::LiftManagerWorker(QObject *parent)
    : QObject(parent), mBuilding{new Building(queues, this)},
      mLift{new Lift(mBuilding, capacity, 500, this)}
{
    connect(mLift, &Lift::arrivedToNewFloor, this,
            &LiftManagerWorker::liftLevelChanged);

    connect(mLift, &Lift::passengersChanged, this,
            &LiftManagerWorker::peopleInLiftChanged);

    connect(mBuilding, &Building::peopleRequestingLiftChanged, this,
            &LiftManagerWorker::peopleOnFloorChanged);
}

void LiftManagerWorker::runLift()
{
    emit addEmptyFloors(floorCount);
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
