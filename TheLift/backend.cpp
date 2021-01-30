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
#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
}

int BackEnd::liftFloor() const
{
    return mLiftFloor;
}

int BackEnd::liftCapacity() const
{
    return mLiftCapacity;
}

QString BackEnd::peopleInLift() const
{
    return mPeopleInLift;
}

void BackEnd::setLiftFloor(int liftFloor)
{
    if (mLiftFloor == liftFloor) {
        return;
    }
    mLiftFloor = liftFloor;
    emit liftFloorChanged();
}

void BackEnd::setLiftCapacity(int liftCapacity)
{
    if (mLiftCapacity == liftCapacity) {
        return;
    }
    mLiftCapacity = liftCapacity;
    emit liftCapacityChanged();
    emit liftNewCapacity(mLiftCapacity);
}

void BackEnd::setPeopleInLift(const QString &peopleInLift)
{
    if (mPeopleInLift == peopleInLift) {
        return;
    }
    mPeopleInLift = peopleInLift;
    emit peopleInLiftChanged();
}
