#include "applicationlist.h"
#include <QDir>
#include <qdebug.h>

ApplicationList::ApplicationList(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(&m_finder, SIGNAL(appFound(Application*)), this, SLOT(append(Application*)));
    connect(&m_finder, SIGNAL(isReady()), this, SLOT(appsReady()));
    m_finder.run();
}

ApplicationList::~ApplicationList()
{
    qDeleteAll(this->m_data);
}

int ApplicationList::count() const
{
    return m_data.count();
}

QObject* ApplicationList::get(int index)
{
    return m_data.at(index);
}

int ApplicationList::rowCount(const QModelIndex &) const
{
    return count();
}

QVariant ApplicationList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() > (m_data.size()-1) )
        return QVariant();

    Application* obj = m_data.at(index.row());
    switch(role)
    {
        case Qt::DisplayRole:
            return QVariant::fromValue(obj->nameLocalized());
        case SearchRole:
            return QVariant::fromValue(obj->searchTerms().join(" "));
        case IconRole:
            return QVariant::fromValue(obj->icon());
        case CommentRole:
            return QVariant::fromValue(obj->comment());
        case IsTerminalRole:
            return QVariant::fromValue(obj->isTerminal());
        case IsHiddenRole:
            return QVariant::fromValue(obj->isHidden());
        case IsNoDisplayRole:
            return QVariant::fromValue(obj->isNoDisplay());
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ApplicationList::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(IconRole, QByteArray("icon"));
    roles.insert(SearchRole, QByteArray("search"));
    roles.insert(CommentRole, QByteArray("comment"));
    roles.insert(IsTerminalRole, QByteArray("isTerminal"));
    roles.insert(IsHiddenRole, QByteArray("isHidden"));
    roles.insert(IsNoDisplayRole, QByteArray("isNoDisplay"));
    return roles;
}

void ApplicationList::append(Application *item)
{
    // qDebug() << "Adding app:" << item->name();
    if (!item->isHidden())
    {
        beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
        m_data.append(item);
        endInsertRows();
        emit countChanged();
    }
}

void ApplicationList::appsReady()
{
    // qDebug() << "Apps Ready";
    emit ready();
}
