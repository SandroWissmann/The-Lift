#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QVector>

class Building : public QObject {
    Q_OBJECT
public:
    explicit Building(const QVector<QVector<int>> &queues,
                      QObject *parent = nullptr);

    void sendAllPeopleRequestingLift();

    bool allQueuesEmpty() const;

    std::optional<int> highestFloorAboveLiftPushedDown(int liftPos) const;

    std::optional<int> nextFloorAboveLiftPushedUp(int liftPos) const;

    std::optional<int> nextFloorUnderLiftPushedDown(int liftPos) const;

    std::optional<int> lowestFloorUnderLiftPushedUp(int liftPos) const;

    QVector<int> peopleOnFloorWaiting(int floor) const;

    QVector<int> removePeopleWhoWantToGoDown(int maxSize, int floor);

    QVector<int> removePeopleWhoWantToGoUp(int maxSize, int floor);

    int floorsCount() const;

public slots:
    void addPerson(int person, int floor);

signals:
    void peopleRequestingLiftChanged(const QVector<int> persons, int floor);
    void noPeopleWaiting();

private:
    QVector<QVector<int>> mQueues;
};

#endif // BUILDING_H
