/* The Lift
 * Copyright (C) 2021  Sandro Wißmann
 *
 * The Lift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Lift is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The Lift If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/The-Lift
 */
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
    Q_PROPERTY(QString liftStarted READ liftStarted WRITE setLiftStarted NOTIFY
                   liftStartedChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);

    int liftFloor() const;
    int liftCapacity() const;
    QString peopleInLift() const;
    bool liftStarted() const;

public slots:
    void setLiftFloor(int liftFloor);
    void setLiftCapacity(int liftCapacity);
    void setPeopleInLift(const QString &peopleInLift);
    void setLiftStarted(bool liftStarted);

signals:
    void liftFloorChanged();
    void liftCapacityChanged();
    void peopleInLiftChanged();
    void liftStartedChanged();

    void liftNewCapacity(int capacity);
    void liftNewStarted(int liftStarted);

private:
    int mLiftFloor;
    int mLiftCapacity;
    QString mPeopleInLift;
    bool mLiftStarted;
};

#endif // BACKEND_H
