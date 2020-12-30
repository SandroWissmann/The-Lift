#include "lift.h"

Lift::Lift(const Queues &queues, int capacity)
    : mQueues{queues}, mCapacity{capacity}
{
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

            if (queuesEmpty(mQueues) && mPassangers.empty()) {
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

std::vector<int> Lift::visitedFloors() const
{
    return mVisitedFloors;
}

void Lift::releasePassengersWithCurrentFloorDestination()
{
    mPassangers.erase(mCurrentFloor);
}

void Lift::goUp()
{
    releasePassengersWithCurrentFloorDestination();
    addPeopleWhoWantToGoUp(mQueues[mCurrentFloor]);
    if (mPassangers.empty()) {
        if (goUpToNextFloorPushedUp()) {
            return;
        }
        if (goUpToHighestFloorPushedDown()) {
            changeDirection();
            addPeopleWhoWantToGoDown(mQueues[mCurrentFloor]);
            return;
        }
        changeDirection();
    }
    else {
        goUpWithPassengers();
    }
}

void Lift::addPeopleWhoWantToGoUp(std::vector<int> &peopleOnFloor)
{
    std::vector<int> newPassengers;

    for (const auto &person : peopleOnFloor) {
        if (newPassengers.size() + mPassangers.size() >= mCapacity) {
            break;
        }
        if (person > mCurrentFloor) {
            newPassengers.push_back(person);
        }
    }

    movePeopleIntoLift(mPassangers, peopleOnFloor, newPassengers);
}

bool Lift::goUpToNextFloorPushedUp()
{
    auto optNextFloorUp = nextFloorAboveLiftPushedUp(mCurrentFloor, mQueues);
    if (optNextFloorUp) {
        arriveToFloor(*optNextFloorUp);
        return true;
    }
    return false;
}

bool Lift::goUpToHighestFloorPushedDown()
{
    auto optHighestFloorDown =
        highestFloorAboveLiftPushedDown(mCurrentFloor, mQueues);
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
        mPassangers.cbegin(), mPassangers.cend(),
        [curr = mCurrentFloor](const auto &val) { return val > curr; });

    // there should be always a person who wants to get higher
    assert(itPosPassengerUp != mPassangers.cend());

    auto optPosUp = nextFloorAboveLiftPushedUp(mCurrentFloor, mQueues);
    if (optPosUp && *optPosUp < *itPosPassengerUp) {
        return *optPosUp;
    }
    return *itPosPassengerUp;
}

void Lift::goDown()
{
    releasePassengersWithCurrentFloorDestination();
    addPeopleWhoWantToGoDown(mQueues[mCurrentFloor]);
    if (mPassangers.empty()) {
        if (goDownToNextFloorPushedDown()) {
            return;
        }
        if (goDownToLowestFloorPushedUp()) {
            changeDirection();
            addPeopleWhoWantToGoUp(mQueues[mCurrentFloor]);
            return;
        }
        if (!queuesEmpty(mQueues)) {
            changeDirection();
        }
    }
    else {
        goDownWithPassengers();
    }
}

void Lift::addPeopleWhoWantToGoDown(std::vector<int> &peopleOnFloor)
{
    std::vector<int> newPassengers;

    for (const auto &person : peopleOnFloor) {
        if (newPassengers.size() + mPassangers.size() >= mCapacity) {
            break;
        }
        if (person < mCurrentFloor) {
            newPassengers.push_back(person);
        }
    }

    movePeopleIntoLift(mPassangers, peopleOnFloor, newPassengers);
}

bool Lift::goDownToNextFloorPushedDown()
{
    auto optNextFloorDown =
        nextFloorUnderLiftPushedDown(mCurrentFloor, mQueues);
    if (optNextFloorDown) {
        arriveToFloor(*optNextFloorDown);
        return true;
    }
    return false;
}

bool Lift::goDownToLowestFloorPushedUp()
{
    auto optLowestFloorUp =
        lowestFloorUnderLiftPushedUp(mCurrentFloor, mQueues);
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
        mPassangers.crbegin(), mPassangers.crend(),
        [curr = mCurrentFloor](const auto &val) { return val < curr; });
    // there should be always a person who wants to get down
    assert(itPosPassengerDown != mPassangers.crend());

    auto optPosDown = nextFloorUnderLiftPushedDown(mCurrentFloor, mQueues);
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

Direction Lift::direction() const
{
    return mDirection;
}

bool queuesEmpty(Queues &queues)
{
    for (const auto &queue : queues) {
        if (!queue.empty()) {
            return false;
        }
    }
    return true;
}

void movePeopleIntoLift(std::multiset<int> &passengers,
                        std::vector<int> &peopleOnFloor,
                        std::vector<int> &newPassengers)
{
    for (const auto &newPassenger : newPassengers) {
        peopleOnFloor.erase(std::find(peopleOnFloor.begin(),
                                      peopleOnFloor.end(), newPassenger));
    }

    for (const auto &newPassenger : newPassengers) {
        passengers.insert(newPassenger);
    }
}

std::optional<int> highestFloorAboveLiftPushedDown(int liftPos,
                                                   const Queues &queues)
{
    for (std::size_t i = queues.size() - 1;
         i != static_cast<std::size_t>(liftPos); --i) {
        for (const auto &person : queues[i]) {
            if (person < i) { // person wants to go down
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> nextFloorAboveLiftPushedUp(int liftPos, const Queues &queues)
{
    if (std::size_t(liftPos) >= queues.size() - 2) {
        return {};
    }
    for (std::size_t i = liftPos + 1; i < queues.size(); ++i) {
        for (const auto &person : queues[i]) {
            if (person > i) {
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> nextFloorUnderLiftPushedDown(int liftPos,
                                                const Queues &queues)
{
    if (liftPos <= 1) {
        return {};
    }
    for (std::size_t i = liftPos - 1; i != std::size_t(0) - 1; --i) {
        for (const auto &person : queues[i]) {
            if (person < i) {
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> lowestFloorUnderLiftPushedUp(int liftPos,
                                                const Queues &queues)
{
    for (std::size_t i = 0; i < static_cast<std::size_t>(liftPos); ++i) {
        for (const auto &person : queues[i]) {
            if (person > i) { // person wants to go up
                return {i};
            }
        }
    }
    return {};
}

std::optional<int>
passengerDestinationLowerThanLiftPos(int liftPos,
                                     const std::multiset<int> &passengers)
{
    auto it = std::find_if(
        passengers.crbegin(), passengers.crend(),
        [curr = liftPos](int passenger) { return passenger < curr; });
    if (it != passengers.crend()) {
        return {*it};
    }
    return {};
}

std::optional<int>
passengerDestinationHigherThanLiftPos(int liftPos,
                                      const std::multiset<int> &passengers)
{
    auto it = std::find_if(
        passengers.cbegin(), passengers.cend(),
        [curr = liftPos](int passenger) { return passenger > curr; });
    if (it != passengers.cend()) {
        return {*it};
    }
    return {};
}