#include "applicationfilter.h"
#include "applicationlist.h"
#include <QHash>
#include <QByteArray>

ApplicationFilter::ApplicationFilter(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    m_settings = new Settings();
    m_filter_name = "";
    m_show_no_display = false;
    m_show_terminal = m_settings->getBool("base/show_terminal_apps", false);
}

QObject *ApplicationFilter::get(QModelIndex index)
{
    QModelIndex source = this->mapToSource(index);
    return ((ApplicationList*) this->sourceModel())->get(source.row());
}

void ApplicationFilter::setFilterName(QString f)
{
    m_filter_name = f;
    invalidateFilter();
}

void ApplicationFilter::setFilterShowNoDisplay(bool showNoDisplay)
{
    m_show_no_display = showNoDisplay;
    invalidateFilter();
}

void ApplicationFilter::toggleFilterShowNoDisplay()
{
    m_show_no_display = !m_show_no_display;
    invalidateFilter();
}

void ApplicationFilter::setFilterShowTerminal(bool showTerminal)
{
    m_show_terminal = showTerminal;
    invalidateFilter();
}

bool ApplicationFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexItem = sourceModel()->index(sourceRow, 0, sourceParent);
    bool isNoDisplay = sourceModel()->data(indexItem, ApplicationList::IsNoDisplayRole).toBool();
    bool isTerminal = sourceModel()->data(indexItem, ApplicationList::IsTerminalRole).toBool();

    return ((isNoDisplay && m_show_no_display) || !isNoDisplay)
            && ((isTerminal && m_show_terminal) || !isTerminal)
            && (sourceModel()->data(indexItem,  ApplicationList::SearchRole).toString()
                    .contains(m_filter_name, Qt::CaseInsensitive)
            );
}

bool ApplicationFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return QString::localeAwareCompare(
                sourceModel()->data(left, Qt::DisplayRole).toString(),
                sourceModel()->data(right, Qt::DisplayRole).toString()
                ) < 0;
}
