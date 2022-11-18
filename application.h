#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QSettings>

#define DESKTOP_GROUP_ENTRY_NAME        "Desktop Entry"
#define DESKTOP_KEY_NAME                "Name"
#define DESKTOP_KEY_GENERIC_NAME        "GenericName"
#define DESKTOP_KEY_LOCALE_GENERIC_NAME "GenericName[%1]"
#define DESKTOP_KEY_VERSION             "Version"
#define DESKTOP_KEY_TERMINAL            "Terminal"
#define DESKTOP_KEY_CATEGORIES          "Categories"
#define DESKTOP_KEY_TYPE                "Type"
#define DESKTOP_KEY_ICON                "Icon"
#define DESKTOP_KEY_EXEC                "Exec"
#define DESKTOP_KEY_COMMENT             "Comment"
#define DESKTOP_KEY_NODISPLAY           "NoDisplay"
#define DESKTOP_KEY_LOCALE_NAME         "Name[%1]"
#define DESKTOP_SHOULD_HIDE_REGEXP      "(compton|picom|x11vnc|electron|openjdk|lstop|mpv|stoken-gui|cmake-gui|qvidcap|qv4l2|avahi-discover|bssh|bvnc)"

/**
 * @brief The DesktopFile class
 *
 * Parsed a desktop file and provides a Model for it
 */

class Application :public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString name_localized READ nameLocalized WRITE setNameLocalized NOTIFY nameLocalizedChanged)
    Q_PROPERTY(QString generic_name READ genericName WRITE setGenericName NOTIFY genericNameChanged)
    Q_PROPERTY(QString generic_name_localized READ genericNameLocalized WRITE setGenericNameLocalized NOTIFY genericNameLocalizedChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(QString exec READ exec WRITE setExec NOTIFY execChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QStringList categories READ categories WRITE setCategories NOTIFY categoriesChanged)
    Q_PROPERTY(bool terminal READ terminal WRITE setTerminal NOTIFY terminalChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(bool noDisplay READ noDisplay WRITE setNoDisplay NOTIFY noDisplayChanged)
    Q_PROPERTY(bool isHidden READ isHidden WRITE setIsHidden NOTIFY isHiddenChanged)
    Q_PROPERTY(bool isValid READ isValid WRITE setIsValid NOTIFY isValidChanged)

public:
    explicit Application(QString fileName, QObject* parent = 0);
    Q_INVOKABLE bool parse();
    Q_INVOKABLE bool run();

    QString fileName() const;
    QString version() const;
    bool terminal() const;
    QStringList categories() const;
    QString type() const;
    QString icon() const;
    QString exec() const;
    QString comment() const;
    QString name() const;
    QString nameLocalized() const;
    QString genericName() const;
    QString genericNameLocalized() const;
    QStringList searchTerms() const;
    bool noDisplay() const;
    bool isHidden() const;
    bool isValid() const;

public slots:
    void setFileName(QString fileName);
    void setVersion(QString version);
    void setTerminal(bool terminal);
    void setCategories(QStringList categories);
    void setType(QString type);
    void setIcon(QString icon);
    void setExec(QString exec);
    void setComment(QString comment);
    void setName(QString name);
    void setNameLocalized(QString name);
    void setGenericName(QString name);
    void setGenericNameLocalized(QString name);
    void setNoDisplay(bool noDisplay);
    void setIsHidden(bool isHidden);
    void setIsValid(bool isValid);

signals:
    void fileNameChanged(QString fileName);
    void versionChanged(QString version);
    void terminalChanged(bool terminal);
    void categoriesChanged(QStringList categories);
    void typeChanged(QString type);
    void iconChanged(QString icon);
    void execChanged(QString exec);
    void commentChanged(QString comment);
    void nameChanged(QString name);
    void nameLocalizedChanged(QString name);
    void genericNameChanged(QString name);
    void genericNameLocalizedChanged(QString name);
    void noDisplayChanged(bool noDisplay);
    void isHiddenChanged(bool isHidden);
    void isValidChanged(bool isValid);

private:
    QString m_fileName;
    QString m_version;
    bool m_terminal = false;
    QStringList m_categories;
    QString m_type;
    QString m_icon;
    QString m_exec;
    QString m_comment;
    QString m_generic_name;
    QString m_generic_name_localized;
    QString m_name;
    QString m_name_localized;
    QStringList m_search_terms;
    bool m_hidden = false;
    bool m_noDisplay = false;
    bool m_is_valid = false;
    QRegExp m_shouldHide;

    QVariant getLocalizedValue(QSettings &settings, QString locale, QString key);
    QString escapeValue(QString value);
    bool testFile();
};

#endif // APPLICATION_H
