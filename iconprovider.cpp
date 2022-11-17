#include "iconprovider.h"
#include <QIcon>
#include <QDir>
#include <QFileInfo>
#include <qdebug.h>

IconProvider::IconProvider() :
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    // Store original theme in property
    m_originalThemeName = QIcon::themeName();
    m_themeList << m_originalThemeName << ICONPROVIDER_LOOKUP_THEMES;
    // Add home directory icons
    QString localFolder = QDir::homePath() + ICONPROVIDER_LOCAL_ICONS_PATH;
    QStringList paths = QIcon::themeSearchPaths();
    paths.append(localFolder);
    QIcon::setThemeSearchPaths(paths);
}


QPixmap IconProvider::searchThemeIcon(QString search)
{
    // qDebug() << "Searching theme icon: " << search;
    // Remove extension
    // ( for ex.: java apps have icons specified as sun-jcontrol-jdk8.png )
    if (search.contains(QRegExp(ICONPROVIDER_EXTENSION_SEARCH)))
    {
        search = search.left(search.length() - 4);
    }

    // Lookup in themes, beginning with the original theme
    for(int i = 0; i < m_themeList.size(); ++i)
    {
        // qDebug() << "Searching in theme: " << m_themeList.at(i);
        QIcon::setThemeName(m_themeList.at(i));
        if (QIcon::hasThemeIcon(search))
        {
            return QIcon::fromTheme(search).pixmap(QSize(ICONPROVIDER_DEFAULT_SIZE));
        }
    }

    return QPixmap();
}

QString IconProvider::searchPixmapPath(QString search)
{
    // Try to look it up in the /user/share/pixmaps folder directly
    QFileInfo check(ICONPROVIDER_PIXMAPS_PATH + search);
    if (check.exists())
    {
        return QString(ICONPROVIDER_PIXMAPS_PATH + search);
    }

    // If the search string doesnt have an extension look it up with supported
    // extensions applied or if the searchstring has an extension remove it
    QString noExt = search;
    if (search.contains(QRegExp(ICONPROVIDER_EXTENSION_SEARCH)))
    {
        // if the searchstring does have an extension remove it
        // ( for ex.: teamspeak3 has teamspeak3.xpm in its
        // .desktop file but the icon is named teamspeak3.png )
        noExt = search.left(search.length() - 4);
    }

    // Check with other known extensions in the folder
    QStringList lookupExtensions;
    lookupExtensions << ICONPROVIDER_LOOKUP_EXTS;
    for(int i = 0; i < lookupExtensions.size(); ++i)
    {
        check.setFile(ICONPROVIDER_PIXMAPS_PATH + noExt + lookupExtensions.at(i));
        if (check.exists())
        {
            return QString(ICONPROVIDER_PIXMAPS_PATH + noExt + lookupExtensions.at(i));
        }
    }
    return QString("");
}

QPixmap IconProvider::checkIconPath(const QString &path)
{
    // qDebug() << "Loading image: " << path;
    QPixmap img = QPixmap(path);
    if (img.isNull())
           return QPixmap(ICONPROVIDER_UNKNOWN_ICON);
    return img;
}

QPixmap IconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    // If the icon search string is empty ( it was not set ) the return unknown icon
    if (id.isEmpty() || id == "")
        return QPixmap(ICONPROVIDER_UNKNOWN_ICON);

    // If the icon has a theme icon return it
    QPixmap themeIcon = this->searchThemeIcon(id);
    if (!themeIcon.isNull())
        return themeIcon;

    // If it is a full path ( begins with / ) then load it from the path and return it
    if (id.contains(QRegExp("^/")))
        return this->checkIconPath(id);

    // If it is not a full path but has extension in the name
    if (id.contains(QRegExp(ICONPROVIDER_EXTENSION_SEARCH)))
    {
        // Try to look it up in the /user/share/pixmaps folder
        QString pixmapPath = this->searchPixmapPath(id);
        if (!pixmapPath.isEmpty() && pixmapPath != "")
        {
            return this->checkIconPath(pixmapPath);
        }
    }

    // Try to look it up in the /user/share/pixmaps folder
    QString pixmapPath = this->searchPixmapPath(id);
    if (!pixmapPath.isEmpty() && pixmapPath != "")
        return this->checkIconPath(pixmapPath);

    // No icon found report it and return default unknown icon
    qDebug() << "! No icon found: " << id;
    return QPixmap(ICONPROVIDER_UNKNOWN_ICON);

}
