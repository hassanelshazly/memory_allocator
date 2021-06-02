#include <QApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>

#include "controller.h"
#include "test.cpp"

int main(int argc, char *argv[])
{
    //    testSegment();
    //    testAllocator();
    testAlgorithm();

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QQuickView view;
    Controller controller;

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.engine()->rootContext()->setContextProperty("controller", &controller);
    view.setSource(QUrl(QStringLiteral("qrc:main.qml")));

    QObject *item = view.rootObject();
    QObject::connect(item, SIGNAL(addNewHole()),
                     &controller, SLOT(addNewHole()));
    QObject::connect(item, SIGNAL(addNewSegment()),
                     &controller, SLOT(addNewSegment()));
    QObject::connect(item, SIGNAL(addNewProcess()),
                     &controller, SLOT(addNewProcess()));

    QObject::connect(item, SIGNAL(setup()),
                     &controller, SLOT(setup()));
    QObject::connect(item, SIGNAL(compact()),
                     &controller, SLOT(compact()));

    view.show();
    return app.exec();
}
