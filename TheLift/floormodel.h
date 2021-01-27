#ifndef FLOORMODEL_H
#define FLOORMODEL_H

#include <QAbstractListModel>

#include "floor.h"

class FloorModel : public QAbstractListModel {
public:
    FloorModel(int floorCount, QObject *parent = nullptr);

    enum FloorRoles {
        PeopleWithDestinationsRole = Qt::UserRole + 1,
        RowRole,
        InsertPersonRole
    };

    int rowCount(const QModelIndex &parent) const;

    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QHash<int, QByteArray> roleNames() const;

public slots:
    void changeFloor(int level, const Floor &floor);

private:
    void addEmptyFloors(int count);

    QVector<Floor> mFloors;
};

QVector<Floor> initFloors(int floorCount);

#endif // FLOORMODEL_H
