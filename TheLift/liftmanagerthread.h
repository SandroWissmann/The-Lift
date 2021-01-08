#ifndef LIFTMANAGERTHREAD_H
#define LIFTMANAGERTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>

class LiftManagerThread : public QThread {
    Q_OBJECT
public:
private:
    void run() override;

    int mLevel;
    bool mUp;

private slots:
    void goToNextFloor();
};

#endif // LIFTMANAGERTHREAD_H
