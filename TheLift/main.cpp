#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QQmlContext>
#include <QScopedPointer>

#include "backend.h"
#include "floor.h"
#include "floormodel.h"
#include "liftmanagerthread.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QScopedPointer<LiftManagerThread> liftManagerThread{new LiftManagerThread};
    BackEnd backEnd;
    FloorModel floorModel;

    QObject::connect(liftManagerThread.get(),
                     &LiftManagerThread::liftLevelChanged, &backEnd,
                     &BackEnd::setLiftFloor);

    QObject::connect(liftManagerThread.get(), &LiftManagerThread::finished,
                     liftManagerThread.get(), &QObject::deleteLater);

    QObject::connect(liftManagerThread.get(),
                     &LiftManagerThread::addEmptyFloors, &floorModel,
                     &FloorModel::addEmptyFloors);

    QObject::connect(
        liftManagerThread.get(), &LiftManagerThread::peopleOnFloorChanged,
        [&floorModel](const QVector<int> &peopleOnFloor, int level) {
            floorModel.changeFloor(level, Floor{peopleOnFloor});
        });

    liftManagerThread->start();

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    context->setContextProperty("backend", &backEnd);

    engine.setInitialProperties(
        {{"floorModel", QVariant::fromValue(&floorModel)}});

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // liftManagerThread->start();
    return app.exec();
}
