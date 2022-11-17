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
    if (!QSettings::contains("color/background"))
        QSettings::setValue("colors/background", "#000000");
    if (!QSettings::contains("colors/selection"))
       QSettings::setValue("colors/selection", "#2d75af");
    if (!QSettings::contains("colors/label"))
       QSettings::setValue("colors/label", "#ffffff");
}
