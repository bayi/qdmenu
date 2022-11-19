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
    enum Roles {
        IconRole = Qt::UserRole + 1,
        SearchRole,
        CommentRole,
        IsTerminalRole,
        IsHiddenRole,
        IsNoDisplayRole
    };
    explicit ApplicationList(QObject *parent = 0);
    virtual ~ApplicationList();

    int count() const;
    Q_INVOKABLE QObject* get(int index);

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
