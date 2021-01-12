#ifndef FLOORMODEL_H
#define FLOORMODEL_H

#include <QAbstractListModel>

#include "floor.h"

class FloorModel : public QAbstractListModel {
public:
    FloorModel(QObject *parent = nullptr);

    enum FloorRoles { PeopleWithDestinationsRole = Qt::UserRole + 1 };

    int rowCount(const QModelIndex &parent) const;

    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    void addEmptyFloors(int count);
    void changeFloor(int level, const Floor &floor);

private:
    QVector<Floor> mFloors;
};

QVector<Floor> initFloors(int floorCount);

#endif // FLOORMODEL_H
