#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
}

int BackEnd::liftFloor() const
{
    return mLiftFloor;
}

int BackEnd::liftCapacity() const
{
    return mLiftCapacity;
}

QString BackEnd::peopleInLift() const
{
    return mPeopleInLift;
}

void BackEnd::setLiftFloor(int liftFloor)
{
    if (mLiftFloor == liftFloor) {
        return;
    }
    mLiftFloor = liftFloor;
    emit liftFloorChanged();
}

void BackEnd::setLiftCapacity(int liftCapacity)
{
    if (mLiftCapacity == liftCapacity) {
        return;
    }
    mLiftCapacity = liftCapacity;
    emit liftCapacityChanged();
    emit liftNewCapacity(mLiftCapacity);
}

void BackEnd::setPeopleInLift(const QString &peopleInLift)
{
    if (mPeopleInLift == peopleInLift) {
        return;
    }
    mPeopleInLift = peopleInLift;
    emit peopleInLiftChanged();
}
