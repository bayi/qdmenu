#include "applicationlist.h"
#include <QDir>
#include <qdebug.h>

const int ApplicationList::SearchRole = Qt::UserRole + 1;
const int ApplicationList::NameRole = Qt::UserRole + 2;
const int ApplicationList::NameLocalizedRole = Qt::UserRole + 3;
const int ApplicationList::GenericNameRole = Qt::UserRole + 4;
const int ApplicationList::GenericNameLocalizedRole = Qt::UserRole + 5;
const int ApplicationList::CommentRole = Qt::UserRole + 6;
const int ApplicationList::IsHiddenRole = Qt::UserRole + 7;
const int ApplicationList::IconRole = Qt::UserRole + 8;
const int ApplicationList::ExecRole = Qt::UserRole + 9;
const int ApplicationList::TerminalRole = Qt::UserRole + 10;

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
        case SearchRole:
            return QVariant::fromValue(obj->searchTerms().join(" "));

        case NameRole:
            return QVariant::fromValue(obj->name());

        case Qt::DisplayRole:
        case NameLocalizedRole:
            return QVariant::fromValue(obj->nameLocalized());

        case GenericNameRole:
            return QVariant::fromValue(obj->genericName());

        case GenericNameLocalizedRole:
            return QVariant::fromValue(obj->genericNameLocalized());

        case CommentRole:
            return QVariant::fromValue(obj->comment());

        case IsHiddenRole:
            return QVariant::fromValue(obj->isHidden());

        case IconRole:
            return QVariant::fromValue(obj->icon());

        case ExecRole:
            return QVariant::fromValue(obj->exec());

        case TerminalRole:
            return QVariant::fromValue(obj->terminal());

        default:
            return QVariant::fromValue(obj->nameLocalized());
    }
}

QHash<int, QByteArray> ApplicationList::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(SearchRole, QByteArray("search"));
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(NameLocalizedRole, QByteArray("name_localized"));
    roles.insert(GenericNameRole, QByteArray("generic_name"));
    roles.insert(GenericNameLocalizedRole, QByteArray("generic_name_localized"));
    roles.insert(CommentRole, QByteArray("comment"));
    roles.insert(IsHiddenRole, QByteArray("is_hidden"));
    roles.insert(IconRole, QByteArray("icon"));
    roles.insert(ExecRole, QByteArray("exec"));
    roles.insert(TerminalRole, QByteArray("terminal"));
    return roles;
}

void ApplicationList::append(Application *item)
{
    // @TODO: Setting/Key for showing hidden items
    if (!item->noDisplay() && !item->terminal() && !item->isHidden())
    {
        // qDebug() << "Adding app:" << item->name();
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
