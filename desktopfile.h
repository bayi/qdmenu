#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

#include <QObject>

#define DESKTOP_GROUP_ENTRY_NAME        "Desktop Entry"
#define DESKTOP_KEY_NAME                "Name"
#define DESKTOP_KEY_VERSION             "Version"
#define DESKTOP_KEY_TERMINAL            "Terminal"
#define DESKTOP_KEY_CATEGORIES          "Categories"
#define DESKTOP_KEY_TYPE                "Type"
#define DESKTOP_KEY_ICON                "Icon"
#define DESKTOP_KEY_EXEC                "Exec"
#define DESKTOP_KEY_COMMENT             "Comment"
#define DESKTOP_KEY_NODISPLAY           "NoDisplay"
#define DESKTOP_KEY_LOCALE_NAME         "Name[%1]"

/**
 * @brief The DesktopFile class
 *
 * Parsed a desktop file and provides a Model for it
 *
 * @todo: Parse multiple categories seperated by ;
 */

class DesktopFile :public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(QString exec READ exec WRITE setExec NOTIFY execChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QStringList categories READ categories WRITE setCategories NOTIFY categoriesChanged)
    Q_PROPERTY(bool terminal READ terminal WRITE setTerminal NOTIFY terminalChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(bool noDisplay READ noDisplay WRITE setNoDisplay NOTIFY noDisplayChanged)

    QString m_fileName;
    QString m_version;
    bool m_terminal = false;
    QStringList m_categories;
    QString m_type;
    QString m_icon;
    QString m_exec;
    QString m_comment;
    QString m_name;
    bool m_noDisplay = false;

    bool parseFile();

public:
    explicit DesktopFile(QString fileName, QObject* parent = 0);

    QString version() const;
    bool terminal() const;
    QStringList categories() const;
    QString type() const;
    QString icon() const;
    QString exec() const;
    QString comment() const;
    QString name() const;
    bool noDisplay() const;

signals:

    void versionChanged(QString version);
    void terminalChanged(bool terminal);
    void categoriesChanged(QStringList categories);
    void typeChanged(QString type);
    void iconChanged(QString icon);
    void execChanged(QString exec);
    void commentChanged(QString comment);
    void nameChanged(QString name);
    void noDisplayChanged(bool noDisplay);

public slots:

    void setVersion(QString version);
    void setTerminal(bool terminal);
    void setCategories(QStringList categories);
    void setType(QString type);
    void setIcon(QString icon);
    void setExec(QString exec);
    void setComment(QString comment);
    void setName(QString name);
    void setNoDisplay(bool noDisplay);
};

#endif // DESKTOPFILE_H
