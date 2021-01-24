#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QQmlContext>

#include "backend.h"
#include "floor.h"
#include "floormodel.h"

#include "liftmanagercontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    BackEnd backEnd;

    constexpr int floorsCount = 7;
    constexpr int capacity = 5;
    LiftManagerController liftManagerController(floorsCount, capacity);

    FloorModel floorModel{liftManagerController.floorsCount()};

    // "getter signals"
    QObject::connect(&liftManagerController,
                     &LiftManagerController::liftLevelChanged, &backEnd,
                     &BackEnd::setLiftFloor);

    QObject::connect(&liftManagerController,
                     &LiftManagerController::liftCapacityChanged, &backEnd,
                     &BackEnd::setLiftCapacity);

    QObject::connect(&liftManagerController,
                     &LiftManagerController::peopleInLiftChanged, &backEnd,
                     &BackEnd::setPeopleInLift);

    // "setter signals"
    QObject::connect(&backEnd, &BackEnd::liftNewCapacity,
                     &liftManagerController,
                     &LiftManagerController::changeLiftCapacity);

    QObject::connect(
        &liftManagerController, &LiftManagerController::peopleOnFloorChanged,
        [&floorModel](const QVector<int> &peopleOnFloor, int level) {
            floorModel.changeFloor(level, Floor{peopleOnFloor});
        });

    liftManagerController.start();

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

    return app.exec();
}
