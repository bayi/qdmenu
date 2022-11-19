#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QQuickImageProvider>
#include "settings.h"

#define ICONPROVIDER_UNKNOWN_ICON       "application-x-executable"
#define ICONPROVIDER_ICONS_PATH         "icons"
#define ICONPROVIDER_HOME_ICONS_PATH   ".icons"
#define ICONPROVIDER_PIXMAPS_PATH       "/usr/share/pixmaps/"
#define ICONPROVIDER_LOCAL_ICONS_PATH   "/.local/share/icons"
#define ICONPROVIDER_LOOKUP_THEMES      "gnome" <<  "HighContrast"

/**
 * @brief The IconProvider class
 *
 * Provides icons from .desktop files Icon= entry
 */
class IconProvider : public QQuickImageProvider
{
    Settings* m_settings;
    QString m_themeName;
    QStringList m_themeList;
    QStringList m_iconExtensions = {"png", "svg", "xpm"};
    QStringList m_iconDirs;

    QPixmap defaultIcon() const;
    QPixmap searchIcon(QString search) const;
    QString lookupIconExtension(QString icon) const;

public:
    explicit IconProvider();

    QPixmap requestPixmap(const QString &id, QSize *size , const QSize &requestedSize);
};

#endif // ICONPROVIDER_H
