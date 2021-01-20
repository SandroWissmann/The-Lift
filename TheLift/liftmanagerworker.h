#ifndef LIFTMANAGERWORKER_H
#define LIFTMANAGERWORKER_H

#include <QObject>

class Building;
class Lift;

class LiftManagerWorker : public QObject {
    Q_OBJECT

public:
    LiftManagerWorker(int floorsCount, int liftCapacity,
                      QObject *parent = nullptr);

signals:
    void liftLevelChanged(int level);
    void peopleOnFloorChanged(const QVector<int> &peopleOnFloor, int level);
    void peopleInLiftChanged(const QString &peopleInLift);

public slots:
    void runLift();

private slots:
    void goToNextFloor();

private:
    Building *mBuilding;
    Lift *mLift;
};

#endif // LIFTMANAGERWORKER_H
