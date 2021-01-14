#include "liftmanagerthread.h"

#include <QTimer>

constexpr int floorCount = 7;
constexpr int capacity = 5;

void LiftManagerThread::run()
{
    QVector<QVector<int>> queues{{},           {2, 2, 3, 3}, {4, 4, 5, 5},
                                 {6, 6, 6, 6}, {1, 1, 2, 2}, {3, 3, 4, 4},
                                 {1, 1, 1, 1}};

    mBuilding.reset(new Building(queues));
    mLift.reset(new Lift(mBuilding.get(), capacity));

    emit addEmptyFloors(floorCount);

    connect(mLift.get(), &Lift::arrivedToNewFloor, this,
            &LiftManagerThread::liftLevelChanged);

    connect(mLift.get(), &Lift::passengersChanged, this,
            &LiftManagerThread::peopleInLiftChanged);

    emit liftLevelChanged(mLift->currentFloor());

    connect(mBuilding.get(), &Building::peopleRequestingLiftChanged, this,
            &LiftManagerThread::peopleOnFloorChanged);

    mBuilding->sendAllPeopleRequestingLift();

    QTimer::singleShot(0, this, &LiftManagerThread::goToNextFloor);
    exec();
}

void LiftManagerThread::goToNextFloor()
{
    mLift->goToNextFloor();
    QTimer::singleShot(2000, this, &LiftManagerThread::goToNextFloor);
}
