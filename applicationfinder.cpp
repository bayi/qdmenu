#include "applicationfinder.h"
#include <QDebug>

void ApplicationFinder::work()
{
    QStringList appdirs = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation); // XDG Default applications location, user local folder first
    appdirs.append(QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)); // Add Desktop to search path
    QStringList loadedFiles;
    static QRegularExpression removeKey("^.*applications/");
    for(const auto& appdir : qAsConst(appdirs))
    {
        QDirIterator appdirIterator(appdir, QStringList(APPLICATIONS_FILES_GLOB), QDir::Files, QDirIterator::Subdirectories|QDirIterator::FollowSymlinks);
        while(!appdirIterator.next().isEmpty())
        {
            QString fileKey = appdirIterator.filePath().remove(removeKey);
            if (!loadedFiles.contains(fileKey)) {
                Application* app = new Application(appdirIterator.filePath());
                if (app->parse()) {
                    // qDebug() << "App Found: " << app->name();
                    emit appFound(app);
                    loadedFiles.append(fileKey);
                } else delete app;
            }
        }
    }
    appdirs.clear();
}

ApplicationFinder::ApplicationFinder(QObject *parent) :
    QObject(parent)
{}

ApplicationFinder::~ApplicationFinder()
{
    if (m_thread.isRunning())
        m_thread.cancel();
}

void ApplicationFinder::run()
{
    m_thread = QtConcurrent::run(this, &ApplicationFinder::work);
    m_thread_watcher.setFuture(m_thread);
    connect(&m_thread_watcher, SIGNAL(finished()), this, SLOT(workFinished()));
}

void ApplicationFinder::workFinished()
{
    emit isReady();
}
