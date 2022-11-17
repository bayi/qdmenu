#include "applicationsfilter.h"
#include "applications.h"
#include <QHash>
#include <QByteArray>

ApplicationsFilter::ApplicationsFilter(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

void ApplicationsFilter::setFilterName(QString f)
{
    m_filter_name = f;
    invalidateFilter();
}

bool ApplicationsFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexItem = sourceModel()->index(sourceRow, 0, sourceParent);
    QString searchString = sourceModel()->data(indexItem,  Applications::SearchRole).toString();
    return searchString.length() > 0 && searchString.contains(m_filter_name, Qt::CaseInsensitive);
}

bool ApplicationsFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, Applications::NameLocalizedRole);
    QVariant rightData = sourceModel()->data(right, Applications::NameLocalizedRole);
    return QString::localeAwareCompare(leftData.toString(), rightData.toString()) < 0;
}
