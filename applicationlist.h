#ifndef APPLICATIONLIST_H
#define APPLICATIONLIST_H

#include <QAbstractListModel>
#include <QList>
#include <applicationfinder.h>
#include "application.h"

/**
 * @brief The Applications class
 *
 * Generates a list of applications from desktop files
 *
 */
class ApplicationList : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ApplicationList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    ApplicationFinder m_finder;
    QList<Application*> m_data;

public:
    explicit ApplicationList(QObject *parent = 0);
    virtual ~ApplicationList();

    static const int SearchRole;
    static const int NameRole;
    static const int NameLocalizedRole;
    static const int GenericNameRole;
    static const int GenericNameLocalizedRole;
    static const int CommentRole;
    static const int IsHiddenRole;
    static const int IconRole;
    static const int ExecRole;
    static const int TerminalRole;

    int count() const;

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex & = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

signals:
    void countChanged();
    void ready();

private slots:
    void append(Application* item);
    void appsReady();

};

#endif // APPLICATIONLIST_H
