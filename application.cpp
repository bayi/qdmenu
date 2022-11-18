#include "application.h"
#include <QFile>
#include <QSettings>
#include <qdebug.h>

bool readDesktopFile(QIODevice &device, QSettings::SettingsMap &map)
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

bool writeDesktopFile(QIODevice &device, const QSettings::SettingsMap &map)
{
    Q_UNUSED(device);
    Q_UNUSED(map);
    qInfo() << "Only reading of desktop files in supported!";
    return true;
}

// Ignore non-pdo-global-static
const QSettings::Format DesktopFileFormat = QSettings::registerFormat("desktopfile", readDesktopFile, writeDesktopFile);

Application::Application(QString fileName, QObject* parent):
    QObject(parent), m_fileName(fileName)
{
    m_search_terms = QStringList();
    this->m_shouldHide = QRegExp(DESKTOP_SHOULD_HIDE_REGEXP);
    this->parse();
}

bool Application::parse()
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

bool Application::run()
{

}

QString Application::fileName() const
{
    return m_fileName;
}

QString Application::version() const
{
    return m_version;
}

bool Application::terminal() const
{
    return m_terminal;
}

QStringList Application::categories() const
{
    return m_categories;
}

QString Application::type() const
{
    return m_type;
}

QString Application::icon() const
{
    return m_icon;
}

QString Application::exec() const
{
    return m_exec;
}

QString Application::comment() const
{
    return m_comment;
}

QString Application::name() const
{
    return m_name;
}

QString Application::nameLocalized() const
{
    return m_name_localized;
}

QString Application::genericName() const
{
    return m_generic_name;
}

QString Application::genericNameLocalized() const
{
    return m_generic_name_localized;
}

QStringList Application::searchTerms() const
{
    return m_search_terms;
}

bool Application::noDisplay() const
{
    return m_noDisplay;
}

bool Application::isHidden() const
{
    return m_hidden;
}

bool Application::isValid() const
{
    return m_is_valid;
}

void Application::setFileName(QString fileName)
{
    if (m_fileName == fileName)
        return;
    m_fileName = fileName;
    emit fileNameChanged(fileName);
}

void Application::setVersion(QString version)
{
    if (m_version == version)
        return;

    m_version = version;
    emit versionChanged(version);
}

void Application::setTerminal(bool terminal)
{
    if (m_terminal == terminal)
        return;

    m_terminal = terminal;
    emit terminalChanged(terminal);
}

void Application::setCategories(QStringList categories)
{
    if (m_categories == categories)
        return;

    m_categories = categories;
    emit categoriesChanged(categories);
}

void Application::setType(QString type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}

void Application::setIcon(QString icon)
{
    if (m_icon == icon)
        return;

    m_icon = icon;
    emit iconChanged(icon);
}

void Application::setExec(QString exec)
{
    if (m_exec == exec)
        return;

    m_exec = exec;
    emit execChanged(exec);
}

void Application::setComment(QString comment)
{
    if (m_comment == comment)
        return;

    m_comment = comment;
    emit commentChanged(comment);
}

void Application::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Application::setNameLocalized(QString name)
{
    if (m_name_localized == name)
        return;

    m_name_localized = name;
    emit nameLocalizedChanged(name);
}

void Application::setGenericName(QString name)
{
    if (m_generic_name == name)
        return;

    m_generic_name = name;
    emit genericNameChanged(name);
}

void Application::setGenericNameLocalized(QString name)
{
    if (m_generic_name_localized == name)
        return;

    m_generic_name_localized = name;
    emit genericNameLocalizedChanged(name);
}

void Application::setNoDisplay(bool noDisplay)
{
    if (m_noDisplay == noDisplay)
        return;

    m_noDisplay = noDisplay;
    emit noDisplayChanged(noDisplay);
}

void Application::setIsHidden(bool isHidden)
{
    m_hidden = isHidden;
}

void Application::setIsValid(bool isValid)
{
    m_is_valid = isValid;
}

QVariant Application::getLocalizedValue(QSettings &settings, QString locale, QString key)
{
    QString localizedKey = key;
    QVariant value = settings.value(localizedKey.append("[%1]").arg(locale));
    if (value.toString().isEmpty()) return settings.value(key);
    return value;
}

QString Application::escapeValue(QString value)
{
    // http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s03.html
    QString result;
    bool inEscapeSeq = false;
    for (auto chr : value)
    {
        if (inEscapeSeq)
        {
            // ++it; // Next char
            if (chr == 's') result.append(' ');  // Space
            else if (chr == 'n') result.append('\n');  // New line
            else if (chr == 'r') result.append('\r');  // CR
            else if (chr == 't') result.append('\t');  // Tab
            else if (chr == '\\') result.append('\\');  // Backslash
            inEscapeSeq = false;
        } else if (chr == '\\') inEscapeSeq = true; // Backslash, start escape sequence
        else result.append(chr);
    }
    return result;
}

bool Application::testFile()
{
    /*
    if (this->tryexec().isEmpty()) return true; // TryExec property missing, assume the file exists
    QStringList pathList = QString(getenv("PATH")).split(":"); // Get PATH from environment
    for (const auto& path : qAsConst(pathList)) // Loop over paths from PATH
        if (QFile::exists(QString(path).append("/").append(tryexec()))) return true; // If found return true
    */
    return false; // Fallthrough: TryExec was set but file not found on PATH
}
