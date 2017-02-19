#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QQuickImageProvider>

#define ICONPROVIDER_UNKNOWN_ICON       "://icons/unknown.svg"
#define ICONPROVIDER_PIXMAPS_PATH       "/usr/share/pixmaps/"
#define ICONPROVIDER_LOCAL_ICONS_PATH   "/.local/share/icons"
#define ICONPROVIDER_DEFAULT_SIZE       80,80
#define ICONPROVIDER_EXTENSION_SEARCH   "\\.(?:png|xpm|svg)$"
#define ICONPROVIDER_LOOKUP_THEMES      "Adwaita" << "gnome" <<  "HighContrast"
#define ICONPROVIDER_LOOKUP_EXTS        ".png" << ".xpm" << ".svg"

/**
 * @brief The IconProvider class
 *
 * Provides icons from .desktop files Icon= entry
 */
class IconProvider : public QQuickImageProvider
{

    QString m_originalThemeName;

    QPixmap searchThemeIcon(QString search);
    QString searchPixmapPath(QString search);

public:
    explicit IconProvider();

    QPixmap requestPixmap(const QString &id, QSize *size , const QSize &requestedSize);
};

#endif // ICONPROVIDER_H
