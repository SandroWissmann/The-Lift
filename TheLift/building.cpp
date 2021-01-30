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
#include "building.h"

#include <algorithm>
#include <cassert>

Building::Building(const QVector<QVector<int>> &queues, QObject *parent)
    : QObject(parent), mQueues{queues}
{
    assert(queues.size() > 0);
}

Building::Building(int floorsCount, QObject *parent)
    : Building(makeFloors(floorsCount), parent)
{
}

void Building::sendAllPeopleRequestingLift()
{
    for (int i = 0; i < mQueues.size(); ++i) {
        emit peopleRequestingLiftChanged(mQueues[i], i);
    }
}

bool Building::allQueuesEmpty() const
{
    return std::all_of(mQueues.begin(), mQueues.end(),
                       [](auto const &queue) { return queue.empty(); });
}

std::optional<int> Building::highestFloorAboveLiftPushedDown(int liftPos) const
{
    for (int i = mQueues.size() - 1; i != liftPos; --i) {
        for (const auto &person : mQueues[i]) {
            if (person < i) { // person wants to go down
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> Building::nextFloorAboveLiftPushedUp(int liftPos) const
{
    if (liftPos >= mQueues.size() - 2) {
        return {};
    }
    for (int i = liftPos + 1; i < mQueues.size(); ++i) {
        for (const auto &person : mQueues[i]) {
            if (person > i) {
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> Building::nextFloorUnderLiftPushedDown(int liftPos) const
{
    if (liftPos <= 1) {
        return {};
    }
    for (int i = liftPos - 1; i >= 0; --i) {
        for (const auto &person : mQueues[i]) {
            if (person < i) {
                return {i};
            }
        }
    }
    return {};
}

std::optional<int> Building::lowestFloorUnderLiftPushedUp(int liftPos) const
{
    for (int i = 0; i < liftPos; ++i) {
        for (const auto &person : mQueues[i]) {
            if (person > i) { // person wants to go up
                return {i};
            }
        }
    }
    return {};
}

QVector<int> Building::peopleOnFloorWaiting(int floor) const
{
    assert(floor >= 0 && floor < mQueues.size());
    return mQueues[floor];
}

QVector<int> Building::removePeopleWhoWantToGoDown(int maxSize, int floor)
{
    QVector<int> peopleWhoWantToGoDown;
    QVector<int> remainingPersons;

    for (const auto &person : mQueues[floor]) {
        if (peopleWhoWantToGoDown.size() < maxSize && person < floor) {
            peopleWhoWantToGoDown.push_back(person);
        }
        else {
            remainingPersons.push_back(person);
        }
    }
    std::swap(mQueues[floor], remainingPersons);
    emit peopleRequestingLiftChanged(mQueues[floor], floor);
    if (allQueuesEmpty()) {
        emit noPeopleWaiting();
    }
    return peopleWhoWantToGoDown;
}

QVector<int> Building::removePeopleWhoWantToGoUp(int maxSize, int floor)
{
    QVector<int> peopleWhoWantToGoUp;
    QVector<int> remainingPersons;

    for (const auto &person : mQueues[floor]) {
        if (peopleWhoWantToGoUp.size() < maxSize && person > floor) {
            peopleWhoWantToGoUp.push_back(person);
        }
        else {
            remainingPersons.push_back(person);
        }
    }
    std::swap(mQueues[floor], remainingPersons);
    emit peopleRequestingLiftChanged(mQueues[floor], floor);
    if (allQueuesEmpty()) {
        emit noPeopleWaiting();
    }
    return peopleWhoWantToGoUp;
}

int Building::floorsCount() const
{
    return mQueues.size();
}

void Building::addPersonWaitingForLift(int personWaitingForLift, int floor)
{
    assert(floor < mQueues.size() && floor >= 0);
    assert(personWaitingForLift != floor);
    mQueues[floor].push_back(floor);
    emit peopleRequestingLiftChanged(mQueues[floor], floor);
}

void Building::addPersonWaitingForLift(
    const QVector<int> &personsWaitingForLift, int floor)
{
    assert(floor < mQueues.size() && floor >= 0);
    mQueues[floor].reserve(mQueues[floor].size() +
                           personsWaitingForLift.size());
    for (const auto &personWaitingForLift : personsWaitingForLift) {
        assert(personWaitingForLift != floor);
        mQueues[floor].push_back(personWaitingForLift);
    }
    emit peopleRequestingLiftChanged(mQueues[floor], floor);
}

QVector<QVector<int>> makeFloors(int floorsCount)
{
    return QVector<QVector<int>>(floorsCount, QVector<int>{});
}
