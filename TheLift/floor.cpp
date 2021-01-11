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
