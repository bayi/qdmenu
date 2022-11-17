#include "settings.h"
#include <QDebug>

Settings::Settings(QObject* parent) :
  QSettings(parent)
{
    qDebug() << "Config loaded: " << QSettings::fileName();
}

Settings::~Settings()
{}

QVariant Settings::get(const QString &key, const QVariant &def = QVariant())
{
    return QSettings::value(key, def);
}

void Settings::initDefaults()
{
    checkAndSet("colors/background", "#000000");
    checkAndSet("colors/selection", "#2d75af");
    checkAndSet("colors/label", "#ffffff");
    checkAndSet("colors/inputborder", "#6795cc");
}

void Settings::checkAndSet(const QString &key, const QVariant &val)
{
    if (!QSettings::contains("key"))
        QSettings::setValue(key, val);
}
