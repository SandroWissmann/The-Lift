#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

class BackEnd : public QObject {
    Q_OBJECT
    Q_PROPERTY(
        int liftFloor READ liftFloor WRITE setLiftFloor NOTIFY liftFloorChanged)
    Q_PROPERTY(int liftCapacity READ liftCapacity WRITE setLiftCapacity NOTIFY
                   liftCapacityChanged)
    Q_PROPERTY(QString peopleInLift READ peopleInLift WRITE setPeopleInLift
                   NOTIFY peopleInLiftChanged)
public:
    explicit BackEnd(QObject *parent = nullptr);

    int liftFloor() const;
    int liftCapacity() const;

    QString peopleInLift() const;

public slots:
    void setLiftFloor(int liftFloor);
    void setLiftCapacity(int liftCapacity);

    void setPeopleInLift(const QString &peopleInLift);

signals:
    void liftFloorChanged();
    void liftCapacityChanged();

    void peopleInLiftChanged();

private:
    int mLiftFloor;
    int mLiftCapacity;
    QString mPeopleInLift;
};

#endif // BACKEND_H
