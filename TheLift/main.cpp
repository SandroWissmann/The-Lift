#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <cassert>

#include "lift.h"

std::vector<int> the_lift(std::vector<std::vector<int>> queues, int capacity)
{
    Lift lift(queues, capacity);
    lift.emptyQueues();
    return lift.visitedFloors();
}

int main(int argc, char *argv[])
{
    std::vector<std::vector<int>> queues;
    std::vector<int> result;

    // nothing to do
    queues = {{}};
    result = {0};
    assert(the_lift(queues, 1) == result);

    // lift full up and down, but don't block passengers
    queues = {
        {},
        {3, 3, 3, 0, 0, 0, 0, 0, 3},
        {},
        {1, 1, 1},
    };
    result = {0, 1, 3, 1, 0, 1, 3, 1, 0, 1, 0};
    assert(the_lift(queues, 2) == result);

    // lift exactly full
    queues = {{}, {}, {5, 5, 5, 5, 5}, {}, {}, {}, {}};
    result = {0, 2, 5, 0};
    assert(the_lift(queues, 5) == result);

    // up
    queues = {{}, {}, {5, 5, 5}, {}, {}, {}, {}};
    result = {0, 2, 5, 0};
    assert(the_lift(queues, 5) == result);

    // down
    queues = {{}, {}, {1, 1}, {}, {}, {}, {}};
    result = {0, 2, 1, 0};
    assert(the_lift(queues, 5) == result);

    // up and up
    queues = {{}, {3}, {4}, {}, {5}, {}, {}};
    result = {0, 1, 2, 3, 4, 5, 0};
    assert(the_lift(queues, 5) == result);

    // down and down
    queues = {{}, {0}, {}, {}, {2}, {3}, {}};
    result = {0, 5, 4, 3, 2, 1, 0};
    assert(the_lift(queues, 5) == result);

    // yoyo
    queues = {{}, {}, {4, 4, 4, 4}, {}, {2, 2, 2, 2}, {}, {}};
    result = {0, 2, 4, 2, 4, 2, 0};
    assert(the_lift(queues, 2) == result);

    // lift full up
    queues = {{3, 3, 3, 3, 3, 3}, {}, {}, {}, {}, {}, {}};
    result = {0, 3, 0, 3, 0};
    assert(the_lift(queues, 5) == result);

    // lift full down
    queues = {{}, {}, {}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {}, {}, {}};
    result = {0, 3, 1, 3, 1, 3, 1, 0};
    assert(the_lift(queues, 5) == result);

    // lift full up and down
    queues = {{3, 3, 3, 3, 3, 3}, {}, {}, {}, {}, {4, 4, 4, 4, 4, 4}, {}};
    result = {0, 3, 5, 4, 0, 3, 5, 4, 0};
    assert(the_lift(queues, 5) == result);

    // Tricky_queues
    queues = {{}, {0, 0, 0, 6}, {}, {}, {}, {6, 6, 0, 0, 0, 6}, {}};
    result = {0, 1, 5, 6, 5, 1, 0, 1, 0};
    assert(the_lift(queues, 5) == result);

    // Highlander
    queues = {{}, {2}, {3, 3, 3}, {1}, {}, {}, {}};
    result = {0, 1, 2, 3, 1, 2, 3, 2, 3, 0};
    assert(the_lift(queues, 1) == result);

    // Fire drill
    queues = {{},           {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
              {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    result = {0, 6, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1,
              0, 4, 3, 2, 1, 0, 3, 2, 1, 0, 1, 0};
    assert(the_lift(queues, 5) == result);

    // no floors (seg fault)
    queues = {};
    result = {0};
    assert(the_lift(queues, 1) == result);

    // no capacity (infinite loop)
    queues = {{1}, {}};
    result = {0};
    assert(the_lift(queues, 0) == result);

    // passenger not changing floor (infinite loop)
    queues = {{0}};
    result = {0};
    assert(the_lift(queues, 1) == result);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
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
