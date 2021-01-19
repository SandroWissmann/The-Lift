#include "floormodel.h"

#include <QDebug>

FloorModel::FloorModel(QObject *parent) : QAbstractListModel(parent)

{
}

int FloorModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount: " << mFloors.size();

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

void FloorModel::addEmptyFloors(int count)
{
    qDebug() << "add Empty floors";

    beginResetModel();
    mFloors.reserve(count);
    for (int i = 0; i < count; ++i) {
        mFloors.push_back(Floor{});
    }
    endResetModel();
    emit dataChanged(QModelIndex{}, QModelIndex{});
}

void FloorModel::changeFloor(int level, const Floor &floor)
{
    mFloors[level] = floor;
    emit dataChanged(this->index(level), this->index(level));
}
