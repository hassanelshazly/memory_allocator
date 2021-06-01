#include <QApplication>
#include <QQuickView>
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
    view.setInitialProperties({
                            {"holeModel", QVariant::fromValue(controller.holeModel())},
                            {"processModel", QVariant::fromValue(controller.processModel())}
                              });
    view.setSource(QUrl(QStringLiteral("qrc:main.qml")));

    QObject *item = view.rootObject();
    QObject::connect(item, SIGNAL(addNewHole()),
                     &controller, SLOT(addNewHole()));
    QObject::connect(item, SIGNAL(addNewProcess()),
                     &controller, SLOT(addNewProcess()));

    view.show();
    return app.exec();
}
