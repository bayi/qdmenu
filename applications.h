#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <QAbstractListModel>
#include <QList>
#include <QStringList>
#include "desktopfile.h"

#define APPLICATIONS_PATH       "/usr/share/applications"
#define APPLICATIONS_LOCAL_PATH "/.local/share/applications"
#define APPLICATIONS_FILES      "*.desktop"

/**
 * @brief The Applications class
 *
 * Generates a list of applications from desktop files
 *
 */
class Applications : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(Applications)
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

    static const int NameRole;
    static const int IconRole;
    static const int ExecRole;
    static const int TerminalRole;
    QStringList m_files;
    QList<DesktopFile*> m_data;
    QList<DesktopFile*> m_internalData;
    int m_count;
    bool parserRunning = false;

    void parseApplications();
    QStringList readFolder(QString folder);
    void add(DesktopFile* item);
    void sort();

public:
    explicit Applications(QObject *parent = 0);
    virtual ~Applications();

    Q_INVOKABLE DesktopFile* get(int index) const;
    Q_INVOKABLE void filter(QString search);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

signals:
    void countChanged(int count);
    void ready();

public slots:

};

#endif // APPLICATIONS_H
