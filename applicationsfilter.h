#ifndef APPLICATIONSFILTER_H
#define APPLICATIONSFILTER_H

#include <QSortFilterProxyModel>
#include <QObject>

class ApplicationsFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    QString m_filter_name;
public:
    explicit ApplicationsFilter(QObject *parent = nullptr);


    QString filterName() const { return m_filter_name; }
    Q_INVOKABLE void setFilterName(QString filter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif // APPLICATIONSFILTER_H
