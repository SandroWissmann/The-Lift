#ifndef LIFTMANAGERTHREAD_H
#define LIFTMANAGERTHREAD_H

#include "building.h"
#include "lift.h"

#include <QObject>
#include <QScopedPointer>
#include <QThread>
#include <QVector>

class Building;
class Lift;

class LiftManagerThread : public QThread {
    Q_OBJECT
public:
signals:
    void liftLevelChanged(int level);

private slots:
    void goToNextFloor();

private:
    void run() override;

    QScopedPointer<Building> mBuilding;
    QScopedPointer<Lift> mLift;
};

#endif // LIFTMANAGERTHREAD_H
