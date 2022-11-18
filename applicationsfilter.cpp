#include "applicationsfilter.h"
#include "applications.h"
#include <QHash>
#include <QByteArray>

ApplicationsFilter::ApplicationsFilter(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

void ApplicationsFilter::setFilterName(QString f)
{
    m_filter_name = f;
    invalidateFilter();
}

bool ApplicationsFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexItem = sourceModel()->index(sourceRow, 0, sourceParent);
    return sourceModel()->data(indexItem,  Applications::SearchRole).toString()
            .contains(m_filter_name, Qt::CaseInsensitive);
}

bool ApplicationsFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return QString::localeAwareCompare(
                sourceModel()->data(left, Applications::NameLocalizedRole).toString(),
                sourceModel()->data(right, Applications::NameLocalizedRole).toString()
                ) < 0;
}
