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
    int floorsCount() const;
    int liftCapacity() const;

signals:
    void startLift(bool started);

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
