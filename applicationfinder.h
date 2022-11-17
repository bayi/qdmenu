#ifndef APPLICATIONFINDER_H
#define APPLICATIONFINDER_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include "desktopfile.h"

#define APPLICATIONS_PATH       "/usr/share/applications"
#define APPLICATIONS_LOCAL_PATH "/.local/share/applications"
#define APPLICATIONS_FILES      "*.desktop"

class ApplicationFinder : public QObject
{
    Q_OBJECT

    QStringList m_files;
    QFuture<void> m_thread;
    QFutureWatcher<void> m_thread_watcher;

    void work();
    QStringList readFolder(QString folder);

public:
    explicit ApplicationFinder(QObject *parent = 0);
    virtual ~ApplicationFinder();

    void run();

signals:
    void isReady();
    void appFound(DesktopFile*);

private slots:
    void workFinished();
};

#endif // APPLICATIONFINDER_H
