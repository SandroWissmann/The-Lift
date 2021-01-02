#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class BackEnd : public QObject {
    Q_OBJECT
    Q_PROPERTY(
        int liftFloor READ liftFloor WRITE setLiftFloor NOTIFY liftFloorChanged)
public:
    explicit BackEnd(QObject *parent = nullptr);

    int liftFloor() const;

public slots:
    void setLiftFloor(int liftFloor);

signals:
    void liftFloorChanged();

private:
    int mLiftFloor;
};

#endif // BACKEND_H
