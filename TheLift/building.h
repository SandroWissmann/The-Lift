#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QVector>

class Building : public QObject {
    Q_OBJECT
public:
    explicit Building(const QVector<QVector<int>> &queues,
                      QObject *parent = nullptr);

    bool noPersonWaitingForLift() const;

    std::optional<int> highestFloorAboveLiftPushedDown(int liftPos) const;

    std::optional<int> nextFloorAboveLiftPushedUp(int liftPos) const;

    std::optional<int> nextFloorUnderLiftPushedDown(int liftPos) const;

    std::optional<int> lowestFloorUnderLiftPushedUp(int liftPos) const;

    QVector<int> peopleOnFloorWaiting(int floor) const;

    QVector<int> removePeopleWhoWantToGoDown(int maxSize, int floor);

    QVector<int> removePeopleWhoWantToGoUp(int maxSize, int floor);

    int floorsCount() const;

private:
    QVector<QVector<int>> mQueues;
};

#endif // BUILDING_H
