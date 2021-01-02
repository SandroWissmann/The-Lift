#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QQmlContext>
#include <QScopedPointer>

#include "backend.h"
#include "liftmanagerthread.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QScopedPointer<LiftManagerThread> liftManager{new LiftManagerThread};
    BackEnd backEnd;

    QObject::connect(liftManager.get(), &LiftManagerThread::liftLevelChanged,
                     &backEnd, &BackEnd::setLiftFloor);

    QObject::connect(liftManager.get(), &LiftManagerThread::finished,
                     liftManager.get(), &QObject::deleteLater);

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    context->setContextProperty("backend", &backEnd);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    liftManager->start();
    return app.exec();
}
