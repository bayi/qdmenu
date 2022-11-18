#ifndef APPLICATIONFILTER_H
#define APPLICATIONFILTER_H

#include <QSortFilterProxyModel>
#include <QObject>

class ApplicationFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    QString m_filter_name;
public:
    explicit ApplicationFilter(QObject *parent = nullptr);


    QString filterName() const { return m_filter_name; }
    Q_INVOKABLE void setFilterName(QString filter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif // APPLICATIONFILTER_H
