#include "applicationfilter.h"
#include "applicationlist.h"
#include <QHash>
#include <QByteArray>

ApplicationFilter::ApplicationFilter(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

void ApplicationFilter::setFilterName(QString f)
{
    m_filter_name = f;
    invalidateFilter();
}

bool ApplicationFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexItem = sourceModel()->index(sourceRow, 0, sourceParent);
    return sourceModel()->data(indexItem,  ApplicationList::SearchRole).toString()
            .contains(m_filter_name, Qt::CaseInsensitive);
}

bool ApplicationFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return QString::localeAwareCompare(
                sourceModel()->data(left, ApplicationList::NameLocalizedRole).toString(),
                sourceModel()->data(right, ApplicationList::NameLocalizedRole).toString()
                ) < 0;
}
