#include "floormodel.h"

#include <QDebug>

FloorModel::FloorModel(int floorCount, QObject *parent)
    : QAbstractListModel(parent)

{
    addEmptyFloors(floorCount);
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
    if (role == RowRole) {
        return index.row();
    }
    return QVariant{};
}

bool FloorModel::setData(const QModelIndex &index, const QVariant &value,
                         int role)
{
    if (role == InsertPersonRole) {
        mFloors[index.row()].addPerson(value.toInt());
        return true;
    }
    return false;
}

Qt::ItemFlags FloorModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

QHash<int, QByteArray> FloorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PeopleWithDestinationsRole] = "peopleWithDestinations";
    roles[RowRole] = "row";
    roles[InsertPersonRole] = "insertPerson";
    return roles;
}

void FloorModel::addEmptyFloors(int count)
{
    beginResetModel();
    mFloors.reserve(count);
    for (int i = 0; i < count; ++i) {
        mFloors.push_back(Floor{});
    }
    endResetModel();
}

void FloorModel::changeFloor(int level, const Floor &floor)
{
    mFloors[level] = floor;
    emit dataChanged(this->index(level), this->index(level));
}
