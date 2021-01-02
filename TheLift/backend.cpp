#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
}

int BackEnd::liftFloor() const
{
    return mLiftFloor;
}

void BackEnd::setLiftFloor(int liftFloor)
{
    if (mLiftFloor == liftFloor) {
        return;
    }
    mLiftFloor = liftFloor;
    liftFloorChanged();
}
