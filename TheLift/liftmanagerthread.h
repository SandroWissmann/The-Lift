#ifndef LIFTMANAGERTHREAD_H
#define LIFTMANAGERTHREAD_H

#include <QObject>
#include <QThread>

class LiftManagerThread : public QThread {
    Q_OBJECT
public:
signals:
    void liftLevelChanged(int currenLevel);

private:
    void run() override;

    int mLevel{0};
    bool mUp{true};
};

#endif // LIFTMANAGERTHREAD_H
