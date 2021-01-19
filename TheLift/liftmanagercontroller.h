#ifndef LIFTMANAGERCONTROLLER_H
#define LIFTMANAGERCONTROLLER_H

#include <QObject>
#include <QThread>

class LiftManagerController : public QObject {
    Q_OBJECT
public:
    explicit LiftManagerController(QObject *parent = nullptr);
    ~LiftManagerController();

public:
    void start();

signals:
    void startLift();

    void addEmptyFloors(int count);
    void liftLevelChanged(int level);
    void peopleOnFloorChanged(const QVector<int> &peopleOnFloor, int level);
    void peopleInLiftChanged(const QString &peopleInLift);

private:
    QThread mWorkerThread;
};

#endif // LIFTMANAGERCONTROLLER_H
