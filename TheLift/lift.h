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

    void goToNextFloor();

    bool hasPassengers() const;
    int currentFloor() const;

    enum class Direction { up, down };

signals:
    void arrivedToNewFloor(int floor);
    void passengersChanged(QVector<int> passengers);

private:
    void releasePassengersWithCurrentFloorDestination();

    bool goUp();

    void addPeopleWhoWantToGoUp();

    bool goUpWithoutPassengers();

    bool goUpToNextFloorPushedUp();
    bool goUpToHighestFloorPushedDown();

    void goUpWithPassengers();

    int getNextFloorUpWithPerson() const;

    bool goDown();

    void addPeopleWhoWantToGoDown();

    bool goDownWithoutPassengers();

    bool goDownToNextFloorPushedDown();
    bool goDownToLowestFloorPushedUp();

    void goDownWithPassengers();

    int getNextFloorDownWithPerson() const;

    void arriveToFloor(int floor);

    void changeDirection();
    Direction direction() const;

    std::multiset<int> mPassengers{};
    Direction mDirection = Direction::up;
    int mCurrentFloor = 0;
    int mCapacity;

    Building *mBuilding;
};

#endif // LIFT_H
