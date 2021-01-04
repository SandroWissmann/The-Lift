#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>

class Building : public QObject {
    Q_OBJECT
public:
    explicit Building(const std::vector<std::vector<int>> &queues,
                      QObject *parent = nullptr);

    bool noPersonWaitingForLift() const;

    std::optional<int> highestFloorAboveLiftPushedDown(int liftPos) const;

    std::optional<int> nextFloorAboveLiftPushedUp(int liftPos) const;

    std::optional<int> nextFloorUnderLiftPushedDown(int liftPos) const;

    std::optional<int> lowestFloorUnderLiftPushedUp(int liftPos) const;

    std::vector<int> peopleOnFloorWaiting(int floor) const;

    std::vector<int> removePeopleWhoWantToGoDown(int maxSize, int floor);

    std::vector<int> removePeopleWhoWantToGoUp(int maxSize, int floor);

    int floorsCount() const;

private:
    std::vector<std::vector<int>> mQueues;
};

#endif // BUILDING_H
