#ifndef LIFT_H
#define LIFT_H

#include <QObject>

#include <optional>
#include <set>
#include <vector>

class Building;

class Lift : public QObject {
    Q_OBJECT
public:
    Lift(Building *building, int capacity, QObject *parent = nullptr);

    void emptyQueues();

    std::vector<int> visitedFloors() const;

    enum class Direction { up, down };

private:
    void releasePassengersWithCurrentFloorDestination();

    void goUp();

    void addPeopleWhoWantToGoUp();

    bool goUpWithoutPassengers();

    bool goUpToNextFloorPushedUp();
    bool goUpToHighestFloorPushedDown();

    void goUpWithPassengers();

    int getNextFloorUpWithPerson() const;

    void goDown();

    void addPeopleWhoWantToGoDown();

    bool goDownWithoutPassengers();

    bool goDownToNextFloorPushedDown();
    bool goDownToLowestFloorPushedUp();

    void goDownWithPassengers();

    int getNextFloorDownWithPerson() const;

    void arriveToFloor(int floor);

    int currentFloor() const;

    void changeDirection();
    Direction direction() const;

    std::multiset<int> mPassengers{};
    std::vector<int> mVisitedFloors{};
    Direction mDirection = Direction::up;
    int mCurrentFloor = 0;
    int mCapacity;

    Building *mBuilding;
};

std::optional<int>
passengerDestinationLowerThanLiftPos(int liftPos,
                                     const std::multiset<int> &passengers);

std::optional<int>
passengerDestinationHigherThanLiftPos(int liftPos,
                                      const std::multiset<int> &passengers);

#endif // LIFT_H
