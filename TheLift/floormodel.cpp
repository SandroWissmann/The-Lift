#include "floormodel.h"

FloorModel::FloorModel(int floorCount, QObject *parent)
    : QAbstractListModel(parent), mFloors{QVector<Floor>(floorCount, Floor{})}
{
    // test
    mFloors[0] = Floor{QVector<int>{1, 2, 3, 4}};
    mFloors[6] = Floor{QVector<int>{4, 3, 2, 1}};
}

int FloorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mFloors.size();
}

int FloorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant FloorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant{};
    }

    if (role == Qt::DisplayRole) {
        return mFloors[index.row()].asString();
    }
    if (role == PeopleWithDestinationsRole) {
        return mFloors[index.row()].asString();
    }
    return QVariant{};
}

QHash<int, QByteArray> FloorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PeopleWithDestinationsRole] = "peopleWithDestinations";
    return roles;
}
