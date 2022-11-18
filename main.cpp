#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "applications.h"
#include "applicationsfilter.h"
#include "iconprovider.h"
#include "process.h"
#include "settings.h"

/**
 * @todo: SHIFT(ENTER) for sudo
 * @todo: TAB For command (term /{usr}/bin/) / app (.desktop) mode
 */
int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.svg.warning=false"); // Hide buggy SVG icon warnings
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setApplicationName("qdmenu");
    QCoreApplication::setOrganizationName("bayi");
    QCoreApplication::setOrganizationDomain("bayi.hu");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
    Applications* applications = new Applications(app.parent());
    ApplicationsFilter* apps = new ApplicationsFilter(app.parent());

    Settings* settings = new Settings();
    settings->initDefaults();

    apps->setSourceModel(applications);
    apps->sort(0, Qt::AscendingOrder);
    apps->setDynamicSortFilter(false);

    qmlRegisterType<Process>("Process", 1, 0, "Process");
    context->setContextProperty("settings", settings);
    context->setContextProperty("apps", apps);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.addImageProvider(QLatin1String("appicon"), new IconProvider);
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    // qDebug() << "GUI Start";
    return app.exec();
}
