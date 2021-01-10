#ifndef FLOOR_H
#define FLOOR_H

#include <QVector>

class Floor {
public:
    Floor(const QVector<int> &peopleWithDestinations = {});

private:
    QVector<int> mPeopleWithDestinations;
};

#endif // FLOOR_H
