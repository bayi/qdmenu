#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QSettings>
#include "settings.h"

#define IGNORED_APPS_REGEXP      "(compton|picom|x11vnc|electron|openjdk|lstop|mpv|stoken-gui|cmake-gui|qvidcap|qv4l2|avahi-discover|bssh|bvnc)"

/**
 * @brief The DesktopFile class
 *
 * Parsed a desktop file and provides a Model for it
 */

class Application :public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString file_name READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString name_localized READ nameLocalized WRITE setNameLocalized NOTIFY nameLocalizedChanged)
    Q_PROPERTY(QString generic_name READ genericName WRITE setGenericName NOTIFY genericNameChanged)
    Q_PROPERTY(QString generic_name_localized READ genericNameLocalized WRITE setGenericNameLocalized NOTIFY genericNameLocalizedChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(QString keywords READ keywords WRITE setKeywords NOTIFY keywordsChanged)
    Q_PROPERTY(QString exec READ exec WRITE setExec NOTIFY execChanged)
    Q_PROPERTY(QString try_exec READ tryExec WRITE setTryExec NOTIFY tryExecChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(QStringList categories READ categories WRITE setCategories NOTIFY categoriesChanged)
    Q_PROPERTY(QStringList search_terms READ searchTerms WRITE setSearchTerms NOTIFY searchTermsChanged)
    Q_PROPERTY(bool is_terminal READ isTerminal WRITE setIsTerminal NOTIFY isTerminalChanged)
    Q_PROPERTY(bool is_no_display READ isNoDisplay WRITE setIsNoDisplay NOTIFY isNoDisplayChanged)
    Q_PROPERTY(bool is_hidden READ isHidden WRITE setIsHidden NOTIFY isHiddenChanged)

public:
    explicit Application(QString fileName, QObject* parent = 0);
    Q_INVOKABLE bool parse();
    Q_INVOKABLE bool run(QString input);

    QString fileName() const;
    QString name() const;
    QString nameLocalized() const;
    QString genericName() const;
    QString genericNameLocalized() const;
    QString comment() const;
    QString keywords() const;
    QString exec() const;
    QString tryExec() const;
    QString path() const;
    QString icon() const;
    QString type() const;
    QString version() const;
    QStringList categories() const;
    QStringList searchTerms() const;
    bool isTerminal() const;
    bool isNoDisplay() const;
    bool isHidden() const;

public slots:
    void setFileName(QString fileName);
    void setName(QString name);
    void setNameLocalized(QString nameLocalized);
    void setGenericName(QString genericName);
    void setGenericNameLocalized(QString genericNameLocalized);
    void setComment(QString comment);
    void setKeywords(QString keywords);
    void setExec(QString exec);
    void setTryExec(QString tryExec);
    void setPath(QString path);
    void setIcon(QString icon);
    void setType(QString type);
    void setVersion(QString version);
    void setCategories(QStringList categories);
    void setSearchTerms(QStringList searchTerms);
    void setIsTerminal(bool isTerminal);
    void setIsNoDisplay(bool isNoDisplay);
    void setIsHidden(bool isHidden);

signals:
    void fileNameChanged(QString fileName);
    void nameChanged(QString name);
    void nameLocalizedChanged(QString nameLocalized);
    void genericNameChanged(QString genericName);
    void genericNameLocalizedChanged(QString genericNameLocalized);
    void commentChanged(QString comment);
    void keywordsChanged(QString keywords);
    void execChanged(QString exec);
    void tryExecChanged(QString tryExec);
    void pathChanged(QString path);
    void iconChanged(QString icon);
    void typeChanged(QString type);
    void versionChanged(QString version);
    void categoriesChanged(QStringList categories);
    void searchTermsChanged(QStringList searchTerms);
    void isTerminalChanged(bool isTerminal);
    void isNoDisplayChanged(bool isNoDisplay);
    void isHiddenChanged(bool isHidden);

private:
    Settings* m_settings;
    QString m_fileName;
    QString m_name;
    QString m_nameLocalized;
    QString m_genericName;
    QString m_genericNameLocalized;
    QString m_comment;
    QString m_keywords;
    QString m_exec;
    QString m_tryExec;
    QString m_path;
    QString m_icon;
    QString m_type;
    QString m_version;
    QStringList m_categories;
    QStringList m_searchTerms;
    bool m_isTerminal = false;
    bool m_isNoDisplay = false;
    bool m_isHidden = false;

    QVariant getLocalizedValue(QSettings &settings, QString locale, QString key);
    QString escapeValue(QString value);
    bool testFile();
};

#endif // APPLICATION_H
