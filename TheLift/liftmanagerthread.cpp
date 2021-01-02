#include "liftmanagerthread.h"

void LiftManagerThread::run()
{
    emit liftLevelChanged(mLevel);
    for (;;) {
        QThread::msleep(500);

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
    }
}
