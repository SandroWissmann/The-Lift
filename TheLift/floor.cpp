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
#include "floor.h"

Floor::Floor(const QVector<int> &peopleWithDestinations)
    : mPeopleWithDestinations{peopleWithDestinations}
{
}

QString Floor::asString() const
{
    QString result;
    for (const auto &personWithDestination : mPeopleWithDestinations) {
        result.append(QString::number(personWithDestination) + " ");
    }
    return result;
}

void Floor::addPerson(int person)
{
    mPeopleWithDestinations.push_back(person);
}
