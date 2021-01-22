#include "lift.h"

#include "building.h"

#include <QThread>

#include <algorithm>
#include <cassert>

Lift::Lift(Building *building, int capacity, unsigned long delayOpenDoors,
           QObject *parent)
    : QObject(parent), mCapacity{capacity},
      mDelayOpenDoors{delayOpenDoors}, mBuilding{building}
{
    assert(capacity > 0);
    assert(building->floorsCount() > 0);
}

bool Lift::hasPassengers() const
{
    return !mPassengers.empty();
}

int Lift::currentFloor() const
{
    return mCurrentFloor;
}

void Lift::setCapacity(int capacity)
{
    if (mCapacity == capacity) {
        return;
    }
    mCapacity = capacity;
    emit capacityChanged(mCapacity);
}

int Lift::capacity() const
{
    return mCapacity;
}

void Lift::goToNextFloor()
{
    if (mDirection == Direction::up) {
        if (!goUp()) {
            goToNextFloor();
        }
    }
    else if (mDirection == Direction::down) {
        if (mBuilding->allQueuesEmpty() && mPassengers.empty()) {
            arriveToFloor(0);
        }
        else {
            if (!goDown()) {
                goToNextFloor();
            }
        }
    }
    QThread::msleep(mDelayOpenDoors);
    releasePassengersWithCurrentFloorDestination();
}

QString Lift::passengersAsString()
{
    QString passengerStr;
    passengerStr.reserve(mPassengers.size() * 2);
    for (const auto &passenger : mPassengers) {
        passengerStr += QString::number(passenger) + " ";
    }
    return passengerStr;
}

void Lift::releasePassengersWithCurrentFloorDestination()
{
    mPassengers.erase(mCurrentFloor);
    emit passengersChanged(passengersAsString());
}

bool Lift::goUp()
{
    addPeopleWhoWantToGoUp();
    QThread::msleep(mDelayOpenDoors);
    if (mPassengers.empty()) {
        if (goUpToNextFloorPushedUp()) {
            return true;
        }
        if (goUpToHighestFloorPushedDown()) {
            changeDirection();
            addPeopleWhoWantToGoDown();
            return true;
        }
        changeDirection();
        return false;
    }
    else {
        goUpWithPassengers();
    }
    return true;
}

void Lift::addPeopleWhoWantToGoUp()
{
    auto newPassengers = mBuilding->removePeopleWhoWantToGoUp(
        mCapacity - mPassengers.size(), mCurrentFloor);
    mPassengers.insert(newPassengers.begin(), newPassengers.end());
    emit passengersChanged(passengersAsString());
}

bool Lift::goUpToNextFloorPushedUp()
{
    auto optNextFloorUp = mBuilding->nextFloorAboveLiftPushedUp(mCurrentFloor);
    if (optNextFloorUp) {
        arriveToFloor(*optNextFloorUp);
        return true;
    }
    return false;
}

bool Lift::goUpToHighestFloorPushedDown()
{
    auto optHighestFloorDown =
        mBuilding->highestFloorAboveLiftPushedDown(mCurrentFloor);
    if (optHighestFloorDown) {
        arriveToFloor(*optHighestFloorDown);
        return true;
    }
    return false;
}

void Lift::goUpWithPassengers()
{
    auto higherFloor = getNextFloorUpWithPerson();
    arriveToFloor(higherFloor);
}

int Lift::getNextFloorUpWithPerson() const
{
    auto itPosPassengerUp = std::find_if(
        mPassengers.cbegin(), mPassengers.cend(),
        [curr = mCurrentFloor](const auto &val) { return val > curr; });

    // there should be always a person who wants to get higher
    assert(itPosPassengerUp != mPassengers.cend());

    auto optPosUp = mBuilding->nextFloorAboveLiftPushedUp(mCurrentFloor);
    if (optPosUp && *optPosUp < *itPosPassengerUp) {
        return *optPosUp;
    }
    return *itPosPassengerUp;
}

bool Lift::goDown()
{
    addPeopleWhoWantToGoDown();
    QThread::msleep(mDelayOpenDoors);
    if (mPassengers.empty()) {
        if (goDownToNextFloorPushedDown()) {
            return true;
        }
        if (goDownToLowestFloorPushedUp()) {
            changeDirection();
            addPeopleWhoWantToGoUp();
            return true;
        }
        if (!mBuilding->allQueuesEmpty()) {
            changeDirection();
            return false;
        }
    }
    else {
        goDownWithPassengers();
    }
    return true;
}

void Lift::addPeopleWhoWantToGoDown()
{
    auto newPassengers = mBuilding->removePeopleWhoWantToGoDown(
        mCapacity - mPassengers.size(), mCurrentFloor);
    mPassengers.insert(newPassengers.begin(), newPassengers.end());
    emit passengersChanged(passengersAsString());
}

bool Lift::goDownToNextFloorPushedDown()
{
    auto optNextFloorDown =
        mBuilding->nextFloorUnderLiftPushedDown(mCurrentFloor);
    if (optNextFloorDown) {
        arriveToFloor(*optNextFloorDown);
        return true;
    }
    return false;
}

bool Lift::goDownToLowestFloorPushedUp()
{
    auto optLowestFloorUp =
        mBuilding->lowestFloorUnderLiftPushedUp(mCurrentFloor);
    if (optLowestFloorUp) {
        arriveToFloor(*optLowestFloorUp);
        return true;
    }
    return false;
}

void Lift::goDownWithPassengers()
{
    auto lowerFloor = getNextFloorDownWithPerson();
    arriveToFloor(lowerFloor);
}

int Lift::getNextFloorDownWithPerson() const
{
    auto itPosPassengerDown = std::find_if(
        mPassengers.crbegin(), mPassengers.crend(),
        [curr = mCurrentFloor](const auto &val) { return val < curr; });
    // there should be always a person who wants to get down
    assert(itPosPassengerDown != mPassengers.crend());

    auto optPosDown = mBuilding->nextFloorUnderLiftPushedDown(mCurrentFloor);

    if (optPosDown && *optPosDown > *itPosPassengerDown) {
        return *optPosDown;
    }
    return *itPosPassengerDown;
}

void Lift::arriveToFloor(int floor)
{
    mCurrentFloor = floor;
    emit arrivedToNewFloor(floor);
}

void Lift::changeDirection()
{
    if (mDirection == Direction::up) {
        mDirection = Direction::down;
    }
    else {
        mDirection = Direction::up;
    }
}

Lift::Direction Lift::direction() const
{
    return mDirection;
}
