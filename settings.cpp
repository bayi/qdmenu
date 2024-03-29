#include "settings.h"
#include <QDebug>

Settings::Settings(QObject* parent) :
  QSettings(parent)
{
    // qDebug() << "Config loaded: " << QSettings::fileName();
}

Settings::~Settings()
{}

QVariant Settings::get(const QString &key, const QVariant &def = QVariant())
{
    return QSettings::value(key, def);
}

qreal Settings::getNumber(const QString &key, const QVariant &def)
{
    return get(key, def).toReal();
}

bool Settings::getBool(const QString &key, const QVariant &def)
{
    return get(key, def).toBool();
}

void Settings::initDefaults()
{
    checkAndSet("base/ignored_applications_regex", "(compton|picom|x11vnc|electron|openjdk|lstop|mpv|stoken-gui|cmake-gui|qvidcap|qv4l2|avahi-discover|bssh|bvnc)");
    checkAndSet("base/terminal", "i3-sensible-terminal");
    checkAndSet("base/show_terminal_apps", false);
    checkAndSet("base/default_icon", "application-x-executable");
    checkAndSet("base/binary_icon", "application-x-executable");

    checkAndSet("background/bgcolor", "#000000");
    checkAndSet("background/topmargin", 32);

    checkAndSet("icons/selectcolor", "#2d75af");
    checkAndSet("icons/textcolor", "#ffffff");
    checkAndSet("icons/padding", 32);
    checkAndSet("icons/cols", 8);
    checkAndSet("icons/rows", 8);
    checkAndSet("icons/width", 64);
    checkAndSet("icons/height", 64);
    checkAndSet("icons/topmargin", 8);
    checkAndSet("icons/bottommargin", 8);

    checkAndSet("input/height", 32);
    checkAndSet("input/bgcolor", "#ffffff");
    checkAndSet("input/textcolor", "#000000");
    checkAndSet("input/fontsize", 24);
    checkAndSet("input/fontbold", true);
    checkAndSet("input/bordercolor", "#6795cc");
    checkAndSet("input/borderwidth", 2);
    checkAndSet("input/borderradius", 8);

}

void Settings::checkAndSet(const QString &key, const QVariant &val)
{
    if (!QSettings::contains(key))
        QSettings::setValue(key, val);
}
