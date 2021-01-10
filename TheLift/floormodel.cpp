#include "floormodel.h"

FloorModel::FloorModel(int floorCount, QObject *parent)
    : QAbstractListModel(parent), mFloors{QVector<Floor>(floorCount, Floor{})}
{
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
        return QVariant::fromValue<Floor>(mFloors[index.row()]);
    }
    if (role == PeopleWithDestinationsRole) {
        return QVariant::fromValue<Floor>(mFloors[index.row()]);
    }
    return QVariant{};
}

QHash<int, QByteArray> FloorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PeopleWithDestinationsRole] = "peopleWithDestinations";
    return roles;
}
