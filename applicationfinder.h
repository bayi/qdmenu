#ifndef APPLICATIONFINDER_H
#define APPLICATIONFINDER_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include "application.h"

#define APPLICATIONS_FILES_GLOB      "*.desktop"

class ApplicationFinder : public QObject
{
    Q_OBJECT

    QFuture<void> m_thread;
    QFutureWatcher<void> m_thread_watcher;

    void work();

public:
    explicit ApplicationFinder(QObject *parent = 0);
    virtual ~ApplicationFinder();

    void run();

signals:
    void isReady();
    void appFound(Application*);

private slots:
    void workFinished();
};

#endif // APPLICATIONFINDER_H
