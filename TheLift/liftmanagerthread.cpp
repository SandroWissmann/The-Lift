#include "liftmanagerthread.h"

#include <QTimer>

void LiftManagerThread::run()
{
    QVector<QVector<int>> queues{{},           {0, 0, 0, 0}, {0, 0, 0, 0},
                                 {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
                                 {0, 0, 0, 0}};
    int capacity = 5;

    mBuilding.reset(new Building(queues));
    mLift.reset(new Lift(mBuilding.get(), capacity));

    connect(mLift.get(), &Lift::arrivedToNewFloor, this,
            &LiftManagerThread::liftLevelChanged);

    emit liftLevelChanged(mLift->currentFloor());

    QTimer::singleShot(0, this, &LiftManagerThread::goToNextFloor);
    exec();
}

void LiftManagerThread::goToNextFloor()
{
    mLift->goToNextFloor();
    QTimer::singleShot(2000, this, &LiftManagerThread::goToNextFloor);
}
