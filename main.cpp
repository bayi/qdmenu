#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "applications.h"
#include "iconprovider.h"
#include "process.h"
#include "settings.h"

/**
 * @todo: Config file in ~/.config/qmldmenu/
 * @todo: SHIFT(ENTER) for sudo
 * @todo: TAB For command (term /{usr}/bin/) / app (.desktop) mode
 */
int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.svg.warning=false"); // Hide buggy SVG icon warnings
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("qdmenu");
    QCoreApplication::setOrganizationName("bayi");
    QCoreApplication::setOrganizationDomain("bayi.hu");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Settings* settings = new Settings();
    settings->initDefaults();

    qmlRegisterType<Process>("Process", 1, 0, "Process");
    qmlRegisterType<Applications>("Applications", 1, 0, "Applications");
    engine.addImageProvider(QLatin1String("appicon"), new IconProvider);
    engine.rootContext()->setContextProperty("settings", settings);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    // qDebug() << "GUI Start";
    return app.exec();
}
