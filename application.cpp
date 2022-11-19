#include "application.h"
#include <QCoreApplication>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include "desktopfileformat.h"

Application::Application(QString fileName, QObject* parent):
    QObject(parent), m_fileName(fileName)
{
    m_settings = new Settings();
}

bool Application::parse()
{
    static const QSettings::Format DesktopFileFormat = QSettings::registerFormat("desktopfile", desktopFileRead, desktopFileWrite);

    QStringList currentDesktop = QString(getenv("XDG_CURRENT_DESKTOP")).split(QLatin1Char(':'),
    Qt::SplitBehaviorFlags::SkipEmptyParts);
    QString locale = QLocale::system().name().split(QRegExp("_")).at(0);

    QSettings settings(fileName(), DesktopFileFormat);
    QRegExp ignoredApps = QRegExp(m_settings->get("base/ignored_applications_regex", IGNORED_APPS_REGEXP).toString());
    settings.setIniCodec("UTF-8");

    // According to the spec 'Hidden' is used for "Uninstalling" apps, so if its set and true then we mark it as inValid
    if (settings.value(DESKTOP_KEY_HIDDEN).toBool()) return false;

    // If TryExec is set and doesnt exists also mark as invalid
    this->setTryExec(escapeValue(settings.value(DESKTOP_KEY_TRY_EXEC).toString()));
    if (!testFile()) return false;

    // If NotShowIn is set and our DM is in that list then set this file as hidden
    QStringList list = settings.value(DESKTOP_KEY_NOT_SHOW_IN).toStringList();
    for (const auto& str : qAsConst(list))
        if (currentDesktop.contains(str)) setIsHidden(true);

    // If OnlyShowIn is set and our DM is NOT in that list then set this file as hidden
    QStringList onlyShowIn = settings.value(DESKTOP_KEY_ONLY_SHOWN_IN).toStringList();
    if (onlyShowIn.length() > 0) {
        bool found = false;
        for (const auto& str : qAsConst(onlyShowIn))
            if (currentDesktop.contains(str)) found = true;
        setIsHidden(isHidden() || !found);
    }

    // Parse rest of attributes
    setName(escapeValue(settings.value(DESKTOP_KEY_NAME).toString()));
    setNameLocalized(escapeValue(getLocalizedValue(settings, locale, DESKTOP_KEY_NAME).toString()));
    setGenericName(escapeValue(settings.value(DESKTOP_KEY_GENERIC_NAME).toString()));
    setGenericNameLocalized(escapeValue(getLocalizedValue(settings, locale, DESKTOP_KEY_GENERIC_NAME).toString()));
    setComment(escapeValue(getLocalizedValue(settings, locale, DESKTOP_KEY_COMMENT).toString()));
    setKeywords(getLocalizedValue(settings, locale, DESKTOP_KEY_KEYWORDS).toString());
    setExec(escapeValue(settings.value(DESKTOP_KEY_EXEC).toString()));
    setPath(escapeValue(settings.value(DESKTOP_KEY_PATH).toString()));
    setIcon(QString("image://appicon/%1").arg(getLocalizedValue(settings, locale, DESKTOP_KEY_ICON).toString()));
    setType(settings.value(DESKTOP_KEY_TYPE).toString());
    setVersion(settings.value(DESKTOP_KEY_VERSION).toString());
    setCategories(getLocalizedValue(settings, locale, DESKTOP_KEY_CATEGORIES).toStringList());
    setIsTerminal(settings.value(DESKTOP_KEY_TERMINAL).toBool());
    // Force set NoDisplay if its in our ignore list
    setIsNoDisplay(settings.value(DESKTOP_KEY_NO_DISPLAY).toBool() || (ignoredApps.indexIn(exec()) != -1));

    // Precalculate search string for filtering
    m_searchTerms.clear();
    m_searchTerms.append(name());
    m_searchTerms.append(nameLocalized());
    m_searchTerms.append(genericName());
    m_searchTerms.append(genericNameLocalized());
    m_searchTerms.append(comment());
    m_searchTerms.append(keywords());
    m_searchTerms.append(exec());
    emit searchTermsChanged(m_searchTerms);

    return true;
}

bool Application::run(QString input)
{
    // @TODO: Also parse Action, expand field Codes, use Path, fix terminal helper (Partially done)
    // @TODO: Modifier to run with sudo
    // @TODO: Calculator, binaries from (/{usr}/bin), urls ( with protocols ) etc, separate non app launcher
    qDebug() << "Executing: " << exec() << " With Input: " << input;

    // Strip field codes from Exec= line
    QString stripped = exec().remove(QRegExp("%[a-zA-Z]")).trimmed();
    QStringList args = QProcess::splitCommand(stripped);
    QString command = args.takeFirst();
    if (isTerminal())
    {
        qDebug() << "Starting terminal process: " << command << " args: " << args.join(',');
        Settings* settings = new Settings();
        QProcess::startDetached(settings->get("base/terminal", "i3-sensible-terminal").toString(), QStringList() << "-e" << command << args);
    } else {
        qDebug() << "Starting process: " << command << " args: " << args.join(',');
        QProcess::startDetached(command, args);
    }

    // Bye bye...
    QCoreApplication::quit();
    return true; // Just to make the compiler happy ...
}

QString Application::fileName() const
{
    return m_fileName;
}

QString Application::name() const
{
    return m_name;
}

QString Application::nameLocalized() const
{
    return m_nameLocalized;
}

QString Application::genericName() const
{
    return m_genericName;
}

QString Application::genericNameLocalized() const
{
    return m_genericNameLocalized;
}

QString Application::comment() const
{
    return m_comment;
}

QString Application::keywords() const
{
    return m_keywords;
}

QString Application::exec() const
{
    return m_exec;
}

QString Application::tryExec() const
{
    return m_tryExec;
}

QString Application::path() const
{
    return m_path;
}

QString Application::icon() const
{
    return m_icon;
}

QString Application::type() const
{
    return m_type;
}

QString Application::version() const
{
    return m_version;
}

QStringList Application::categories() const
{
    return m_categories;
}

QStringList Application::searchTerms() const
{
    return m_searchTerms;
}

bool Application::isTerminal() const
{
    return m_isTerminal;
}

bool Application::isNoDisplay() const
{
    return m_isNoDisplay;
}

bool Application::isHidden() const
{
    return m_isHidden;
}

void Application::setFileName(QString fileName)
{
    if (m_fileName == fileName)
        return;
    m_fileName = fileName;
    emit fileNameChanged(fileName);
}

void Application::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Application::setNameLocalized(QString nameLocalized)
{
    if (m_nameLocalized == nameLocalized)
        return;

    m_nameLocalized = nameLocalized;
    emit nameLocalizedChanged(nameLocalized);
}

void Application::setGenericName(QString genericName)
{
    if (m_genericName == genericName)
        return;

    m_genericName = genericName;
    emit genericNameChanged(genericName);
}

void Application::setGenericNameLocalized(QString geneircNameLocalized)
{
    if (m_genericNameLocalized == geneircNameLocalized)
        return;

    m_genericNameLocalized = geneircNameLocalized;
    emit genericNameLocalizedChanged(geneircNameLocalized);
}


void Application::setComment(QString comment)
{
    if (m_comment == comment)
        return;

    m_comment = comment;
    emit commentChanged(comment);
}

void Application::setKeywords(QString keywords)
{
    if (m_keywords == keywords)
        return;

    m_keywords = keywords;
    emit keywordsChanged(keywords);
}

void Application::setExec(QString exec)
{
    if (m_exec == exec)
        return;

    m_exec = exec;
    emit execChanged(exec);
}

void Application::setTryExec(QString tryExec)
{
    if (m_tryExec == tryExec)
        return;

    m_tryExec = tryExec;
    emit tryExecChanged(tryExec);
}

void Application::setPath(QString path)
{
    if (m_path == path)
        return;
    m_path = path;
    emit pathChanged(path);
}

void Application::setIcon(QString icon)
{
    if (m_icon == icon)
        return;

    m_icon = icon;
    emit iconChanged(icon);
}

void Application::setType(QString type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}

void Application::setVersion(QString version)
{
    if (m_version == version)
        return;

    m_version = version;
    emit versionChanged(version);
}

void Application::setCategories(QStringList categories)
{
    if (m_categories == categories)
        return;

    m_categories = categories;
    emit categoriesChanged(categories);
}

void Application::setSearchTerms(QStringList searchTerms)
{
    if (m_searchTerms == searchTerms)
        return;
    m_searchTerms = searchTerms;
    emit searchTermsChanged(searchTerms);
}

void Application::setIsTerminal(bool isTerminal)
{
    if (m_isTerminal == isTerminal)
        return;

    m_isTerminal = isTerminal;
    emit isTerminalChanged(isTerminal);
}

void Application::setIsNoDisplay(bool isNoDisplay)
{
    if (m_isNoDisplay == isNoDisplay)
        return;

    m_isNoDisplay = isNoDisplay;
    emit isNoDisplayChanged(isNoDisplay);
}

void Application::setIsHidden(bool isHidden)
{
    if (m_isHidden == isHidden)
        return;

    m_isHidden = isHidden;
    emit isHiddenChanged(isHidden);
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
    if (tryExec().isEmpty()) return true; // TryExec property missing, assume the file exists
    QStringList pathList = QString(getenv("PATH")).split(":"); // Get PATH from environment
    for (const auto& path : qAsConst(pathList)) // Loop over paths from PATH
        if (QFile::exists(QString(path).append("/").append(tryExec()))) return true; // If found return true
    return false; // Fallthrough: TryExec was set but file not found on PATH
}
