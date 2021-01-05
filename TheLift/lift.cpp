#include "lift.h"

#include "building.h"

#include <algorithm>
#include <cassert>

Lift::Lift(Building *building, int capacity, QObject *parent)
    : QObject(parent), mCapacity{capacity}, mBuilding{building}
{
    assert(capacity > 0);
    assert(building->floorsCount() > 0);
    building->setParent(this);
}

void Lift::emptyQueues()
{
    arriveToFloor(0);
    bool goToStartPosition = false;
    for (;;) {
        while (mDirection == Direction::up) {
            goUp();
        }
        while (mDirection == Direction::down) {
            goDown();
            if (mBuilding->noPersonWaitingForLift() && mPassengers.empty()) {
                goToStartPosition = true;
                break;
            }
        }
        if (goToStartPosition) {
            break;
        }
    }
    if (mCurrentFloor != 0) {
        arriveToFloor(0);
    }
}

QVector<int> Lift::visitedFloors() const
{
    return mVisitedFloors;
}

void Lift::releasePassengersWithCurrentFloorDestination()
{
    mPassengers.erase(mCurrentFloor);
}

void Lift::goUp()
{
    releasePassengersWithCurrentFloorDestination();
    addPeopleWhoWantToGoUp();
    if (mPassengers.empty()) {
        if (goUpToNextFloorPushedUp()) {
            return;
        }
        if (goUpToHighestFloorPushedDown()) {
            changeDirection();
            addPeopleWhoWantToGoDown();
            return;
        }
        changeDirection();
    }
    else {
        goUpWithPassengers();
    }
}

void Lift::addPeopleWhoWantToGoUp()
{
    auto newPassengers = mBuilding->removePeopleWhoWantToGoUp(
        mCapacity - mPassengers.size(), mCurrentFloor);
    mPassengers.insert(newPassengers.begin(), newPassengers.end());
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

void Lift::goDown()
{
    releasePassengersWithCurrentFloorDestination();
    addPeopleWhoWantToGoDown();
    if (mPassengers.empty()) {
        if (goDownToNextFloorPushedDown()) {
            return;
        }
        if (goDownToLowestFloorPushedUp()) {
            changeDirection();
            addPeopleWhoWantToGoUp();
            return;
        }
        if (!mBuilding->noPersonWaitingForLift()) {
            changeDirection();
        }
    }
    else {
        goDownWithPassengers();
    }
}

void Lift::addPeopleWhoWantToGoDown()
{
    auto newPassengers = mBuilding->removePeopleWhoWantToGoDown(
        mCapacity - mPassengers.size(), mCurrentFloor);
    mPassengers.insert(newPassengers.begin(), newPassengers.end());
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
    mVisitedFloors.push_back(mCurrentFloor);
}

int Lift::currentFloor() const
{
    return mCurrentFloor;
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
