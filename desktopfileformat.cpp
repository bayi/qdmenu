#include "desktopfileformat.h"

#include <QDebug>

bool desktopFileRead(QIODevice &device, QSettings::SettingsMap &map)
{
    QTextStream stream(&device);
    QString currentSection;
    bool isValid = false;
    for (QString line = stream.readLine(); !line.isNull(); line=stream.readLine())
    {
        line = line.trimmed();
        if (line.isEmpty() && line.startsWith(QLatin1Char('#'))) continue; // If line is empty or is a comment skip it
        if (line.startsWith(QLatin1Char('['))) { // Section start
            currentSection = line.mid(1, line.size() - 2).trimmed();
            if (currentSection == "Desktop Entry") isValid = true;
            continue;
        }
        if (currentSection.isEmpty() || currentSection != "Desktop Entry") continue; // If not in 'Desktop Entry' section yet .. continue
        QString key = line.section('=', 0,0).trimmed(); // Key is the part before the first =
        QString value = line.section('=', 1, -1).trimmed(); // Value is the part after the first =
        if (value.contains(QLatin1Char(';')))
            map.insert(key, value.split(QLatin1Char(';'), Qt::SplitBehaviorFlags::SkipEmptyParts)); // If the value contains ; then its an array so split it
        else
            map.insert(key, value);

    }
    return isValid;
}

bool desktopFileWrite(QIODevice &device, const QSettings::SettingsMap &map)
{
    Q_UNUSED(device);
    Q_UNUSED(map);
    qInfo() << "Only reading of desktop files in supported!";
    return true;
}
