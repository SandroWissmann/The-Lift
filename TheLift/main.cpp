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
    FloorModel floorModel;

    LiftManagerController LiftManagerController;

    QObject::connect(&LiftManagerController,
                     &LiftManagerController::liftLevelChanged, &backEnd,
                     &BackEnd::setLiftFloor);

    QObject::connect(&LiftManagerController,
                     &LiftManagerController::peopleInLiftChanged, &backEnd,
                     &BackEnd::setPeopleInLift);

    QObject::connect(&LiftManagerController,
                     &LiftManagerController::addEmptyFloors, &floorModel,
                     &FloorModel::addEmptyFloors);

    QObject::connect(
        &LiftManagerController, &LiftManagerController::peopleOnFloorChanged,
        [&floorModel](const QVector<int> &peopleOnFloor, int level) {
            floorModel.changeFloor(level, Floor{peopleOnFloor});
        });

    LiftManagerController.start();

    QThread::msleep(20000);

    qDebug() << "rows" << floorModel.rowCount(QModelIndex{});

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
