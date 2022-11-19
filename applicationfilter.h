#ifndef APPLICATIONFILTER_H
#define APPLICATIONFILTER_H

#include <QSortFilterProxyModel>
#include <QObject>
#include "settings.h"

class ApplicationFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Settings* m_settings;
    QString m_filter_name;
    bool m_show_no_display;
    bool m_show_terminal;
public:
    explicit ApplicationFilter(QObject *parent = nullptr);

    Q_INVOKABLE QObject* get(QModelIndex index);

    QString filterName() const { return m_filter_name; }
    Q_INVOKABLE void setFilterName(QString filter);
    Q_INVOKABLE void setFilterShowNoDisplay(bool showNoDisplay);
    Q_INVOKABLE void toggleFilterShowNoDisplay();
    Q_INVOKABLE void setFilterShowTerminal(bool showTerminal);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif // APPLICATIONFILTER_H
