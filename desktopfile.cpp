#include "desktopfile.h"
#include <QFile>
#include <QSettings>
#include <qdebug.h>

DesktopFile::DesktopFile(QString fileName, QObject* parent):
    QObject(parent), m_fileName(fileName)
{
    m_search_terms = QStringList();
    this->m_shouldHide = QRegExp(DESKTOP_SHOULD_HIDE_REGEXP);
    this->parseFile();
}

bool DesktopFile::parseFile()
{
    m_search_terms.clear();
    QString locale = QLocale::system().name().split(QRegExp("_")).at(0);
    QSettings settings(m_fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup(DESKTOP_GROUP_ENTRY_NAME);
    this->setVersion(settings.value(DESKTOP_KEY_VERSION).toString());
    this->setTerminal(settings.value(DESKTOP_KEY_TERMINAL).toBool());
    this->setCategories(settings.value(DESKTOP_KEY_CATEGORIES).toStringList());
    this->setType(settings.value(DESKTOP_KEY_TYPE).toString());
    this->setIcon(QString("image://appicon/%1").arg(settings.value(DESKTOP_KEY_ICON).toString()));
    this->setExec(settings.value(DESKTOP_KEY_EXEC).toString());
    this->setComment(settings.value(DESKTOP_KEY_COMMENT).toString());
    this->setIsHidden(this->m_shouldHide.indexIn(this->exec()) != -1);
    this->setName(settings.value(DESKTOP_KEY_NAME).toString());
    this->setNameLocalized(settings.value(QString(DESKTOP_KEY_LOCALE_NAME).arg(locale)).toString());
    if (nameLocalized().isEmpty())
        this->setNameLocalized(name());
    QString genericName = settings.value(QString(DESKTOP_KEY_LOCALE_GENERIC_NAME).arg(locale)).toString();
    if (genericName.isEmpty())
        this->setGenericName(settings.value(DESKTOP_KEY_GENERIC_NAME).toString());
    else
        this->setGenericName(genericName);
    this->setNoDisplay(settings.value(DESKTOP_KEY_NODISPLAY).toBool());
    m_search_terms.append(name());
    m_search_terms.append(nameLocalized());
    m_search_terms.append(this->genericName());
    m_search_terms.append(genericNameLocalized());
    m_search_terms.append(comment());
    m_search_terms.append(exec());
    return true;
}

QString DesktopFile::version() const
{
    return m_version;
}

bool DesktopFile::terminal() const
{
    return m_terminal;
}

QStringList DesktopFile::categories() const
{
    return m_categories;
}

QString DesktopFile::type() const
{
    return m_type;
}

QString DesktopFile::icon() const
{
    return m_icon;
}

QString DesktopFile::exec() const
{
    return m_exec;
}

QString DesktopFile::comment() const
{
    return m_comment;
}

QString DesktopFile::name() const
{
    return m_name;
}

QString DesktopFile::nameLocalized() const
{
    return m_name_localized;
}

QString DesktopFile::genericName() const
{
    return m_generic_name;
}

QString DesktopFile::genericNameLocalized() const
{
    return m_generic_name_localized;
}

QStringList DesktopFile::searchTerms() const
{
    return m_search_terms;
}

bool DesktopFile::noDisplay() const
{
    return m_noDisplay;
}

bool DesktopFile::isHidden() const
{
    return m_hidden;
}

bool DesktopFile::contains(const QString &s)
{
    return name().contains(s,Qt::CaseInsensitive)
            || nameLocalized().contains(s,Qt::CaseInsensitive)
            || genericName().contains(s, Qt::CaseInsensitive)
            || genericNameLocalized().contains(s, Qt::CaseInsensitive)
            || comment().contains(s, Qt::CaseInsensitive)
            || exec().contains(s, Qt::CaseInsensitive)
            ;
}

void DesktopFile::setVersion(QString version)
{
    if (m_version == version)
        return;

    m_version = version;
    emit versionChanged(version);
}

void DesktopFile::setTerminal(bool terminal)
{
    if (m_terminal == terminal)
        return;

    m_terminal = terminal;
    emit terminalChanged(terminal);
}

void DesktopFile::setCategories(QStringList categories)
{
    if (m_categories == categories)
        return;

    m_categories = categories;
    emit categoriesChanged(categories);
}

void DesktopFile::setType(QString type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}

void DesktopFile::setIcon(QString icon)
{
    if (m_icon == icon)
        return;

    m_icon = icon;
    emit iconChanged(icon);
}

void DesktopFile::setExec(QString exec)
{
    if (m_exec == exec)
        return;

    m_exec = exec;
    emit execChanged(exec);
}

void DesktopFile::setComment(QString comment)
{
    if (m_comment == comment)
        return;

    m_comment = comment;
    emit commentChanged(comment);
}

void DesktopFile::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void DesktopFile::setNameLocalized(QString name)
{
    if (m_name_localized == name)
        return;

    m_name_localized = name;
    emit nameLocalizedChanged(name);
}

void DesktopFile::setGenericName(QString name)
{
    if (m_generic_name == name)
        return;

    m_generic_name = name;
    emit genericNameChanged(name);
}

void DesktopFile::setGenericNameLocalized(QString name)
{
    if (m_generic_name_localized == name)
        return;

    m_generic_name_localized = name;
    emit genericNameLocalizedChanged(name);
}

void DesktopFile::setNoDisplay(bool noDisplay)
{
    if (m_noDisplay == noDisplay)
        return;

    m_noDisplay = noDisplay;
    emit noDisplayChanged(noDisplay);
}

void DesktopFile::setIsHidden(bool isHidden)
{
    m_hidden = isHidden;
}
