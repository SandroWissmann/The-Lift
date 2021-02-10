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
#include <QGuiApplication>
#include <QQmlApplicationEngine>

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

    // "setter signals"
    QObject::connect(&backEnd, &BackEnd::liftNewStarted, &liftManagerController,
                     &LiftManagerController::startLift);

    QObject::connect(
        &liftManagerController, &LiftManagerController::peopleOnFloorChanged,
        [&floorModel](const QVector<int> &peopleOnFloor, int level) {
            floorModel.changeFloor(level, Floor{peopleOnFloor});
        });

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
