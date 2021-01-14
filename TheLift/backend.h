#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

class BackEnd : public QObject {
    Q_OBJECT
    Q_PROPERTY(
        int liftFloor READ liftFloor WRITE setLiftFloor NOTIFY liftFloorChanged)
    Q_PROPERTY(QString peopleInLift READ peopleInLift WRITE setPeopleInLift
                   NOTIFY peopleInLiftChanged)
public:
    explicit BackEnd(QObject *parent = nullptr);

    int liftFloor() const;

    QString peopleInLift() const;

public slots:
    void setLiftFloor(int liftFloor);
    void setPeopleInLift(const QString &peopleInLift);

signals:
    void liftFloorChanged();
    void peopleInLiftChanged();

private:
    int mLiftFloor;
    QString mPeopleInLift;
};

#endif // BACKEND_H
