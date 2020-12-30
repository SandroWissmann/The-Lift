#ifndef LIFT_H
#define LIFT_H

#include <algorithm>
#include <cassert>
#include <optional>
#include <set>
#include <vector>

using Queues = std::vector<std::vector<int>>;

class Lift {
public:
    Lift(const Queues &queues, int capacity);

    void emptyQueues();

    std::vector<int> visitedFloors() const;

    enum class Direction { up, down };

private:
    void releasePassengersWithCurrentFloorDestination();

    void goUp();

    void addPeopleWhoWantToGoUp(std::vector<int> &peopleOnFloor);

    bool goUpWithoutPassengers();

    bool goUpToNextFloorPushedUp();
    bool goUpToHighestFloorPushedDown();

    void goUpWithPassengers();

    int getNextFloorUpWithPerson() const;

    void goDown();

    void addPeopleWhoWantToGoDown(std::vector<int> &peopleOnFloor);

    bool goDownWithoutPassengers();

    bool goDownToNextFloorPushedDown();
    bool goDownToLowestFloorPushedUp();

    void goDownWithPassengers();

    int getNextFloorDownWithPerson() const;

    void arriveToFloor(int floor);

    int currentFloor() const;

    void changeDirection();
    Direction direction() const;

    std::multiset<int> mPassangers{};
    std::vector<int> mVisitedFloors{};
    Direction mDirection = Direction::up;
    int mCurrentFloor = 0;
    int mCapacity;

    Queues mQueues;
};

bool queuesEmpty(Queues &queues);

void movePeopleIntoLift(std::multiset<int> &passengers,
                        std::vector<int> &peopleOnFloor,
                        std::vector<int> &newPassengers);

std::optional<int> highestFloorAboveLiftPushedDown(int liftPos,
                                                   const Queues &queues);

std::optional<int> nextFloorAboveLiftPushedUp(int liftPos,
                                              const Queues &queues);

std::optional<int> nextFloorUnderLiftPushedDown(int liftPos,
                                                const Queues &queues);

std::optional<int> lowestFloorUnderLiftPushedUp(int liftPos,
                                                const Queues &queues);

std::optional<int>
passengerDestinationLowerThanLiftPos(int liftPos,
                                     const std::multiset<int> &passengers);

std::optional<int>
passengerDestinationHigherThanLiftPos(int liftPos,
                                      const std::multiset<int> &passengers);

#endif // LIFT_H
