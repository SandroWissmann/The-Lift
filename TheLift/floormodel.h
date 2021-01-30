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
