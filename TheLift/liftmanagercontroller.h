#ifndef LIFTMANAGERCONTROLLER_H
#define LIFTMANAGERCONTROLLER_H

#include <QObject>
#include <QThread>

class LiftManagerController : public QObject {
    Q_OBJECT
public:
    explicit LiftManagerController(int floorsCount, int liftCapacity,
                                   QObject *parent = nullptr);
    ~LiftManagerController();

public:
    void start();

    int floorsCount() const;
    int liftCapacity() const;

signals:
    void startLift();

    void liftLevelChanged(int level);
    void liftCapacityChanged(int capacity);
    void peopleOnFloorChanged(const QVector<int> &peopleOnFloor, int level);
    void peopleInLiftChanged(const QString &peopleInLift);

    void changeLiftCapacity(int capacity);

private:
    QThread mWorkerThread;
    int mFloorsCount;
    int mLiftCapacity;
};

#endif // LIFTMANAGERCONTROLLER_H
