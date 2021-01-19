#include "liftmanagercontroller.h"

#include "liftmanagerworker.h"

LiftManagerController::LiftManagerController(QObject *parent) : QObject(parent)
{
    auto liftManagerWorker = new LiftManagerWorker;
    liftManagerWorker->moveToThread(&mWorkerThread);
    connect(&mWorkerThread, &QThread::finished, liftManagerWorker,
            &QObject::deleteLater);
    connect(this, &LiftManagerController::startLift, liftManagerWorker,
            &LiftManagerWorker::runLift);

    connect(liftManagerWorker, &LiftManagerWorker::addEmptyFloors, this,
            &LiftManagerController::addEmptyFloors);
    connect(liftManagerWorker, &LiftManagerWorker::liftLevelChanged, this,
            &LiftManagerController::liftLevelChanged);
    connect(liftManagerWorker, &LiftManagerWorker::peopleOnFloorChanged, this,
            &LiftManagerController::peopleOnFloorChanged);
    connect(liftManagerWorker, &LiftManagerWorker::peopleInLiftChanged, this,
            &LiftManagerController::peopleInLiftChanged);

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
