#include "liftmanagerthread.h"

#include <QTimer>

void LiftManagerThread::run()
{
    QTimer::singleShot(0, this, &LiftManagerThread::goToNextFloor);
    exec();
}

void LiftManagerThread::goToNextFloor()
{
    constexpr int maxLevel = 7;
    if (mUp) {
        ++mLevel;
        emit liftLevelChanged(mLevel);
    }
    else {
        --mLevel;
        emit liftLevelChanged(mLevel);
    }
    if (mLevel >= maxLevel) {
        mUp = false;
    }
    if (mLevel <= 0) {
        mUp = true;
    }
    QTimer::singleShot(500, this, &LiftManagerThread::goToNextFloor);
}
