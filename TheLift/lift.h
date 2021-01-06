#ifndef LIFT_H
#define LIFT_H

#include <QObject>
#include <QVector>

#include <optional>
#include <set>

class Building;

class Lift : public QObject {
    Q_OBJECT
public:
    Lift(Building *building, int capacity, QObject *parent = nullptr);

    void emptyQueues();

    QVector<int> visitedFloors() const;

    enum class Direction { up, down };

signals:
    void arrivedToNewFloor(int floor);
    void passengersChanged(QVector<int> passengers);

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
    QVector<int> mVisitedFloors{};
    Direction mDirection = Direction::up;
    int mCurrentFloor = 0;
    int mCapacity;

    Building *mBuilding;
};

#endif // LIFT_H
