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
