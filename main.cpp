#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "applications.h"
#include "iconprovider.h"
#include "process.h"

/**
 * @todo: Config file in ~/.config/qmldmenu/
 * @todo: SHIFT(ENTER) for sudo
 * @todo: TAB For command (term /{usr}/bin/) / app (.desktop) mode
 */
int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.svg.warning=false"); // Hide buggy SVG icon warnings
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Process>("Process", 1, 0, "Process");
    qmlRegisterType<Applications>("Applications", 1, 0, "Applications");
    engine.addImageProvider(QLatin1String("appicon"), new IconProvider);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
