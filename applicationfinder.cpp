#include "applicationfinder.h"
#include <QDebug>

void ApplicationFinder::work()
{
    this->m_files.append(this->readFolder(QDir::homePath() + APPLICATIONS_LOCAL_PATH));
    this->m_files.append(this->readFolder(APPLICATIONS_PATH));
    foreach(QString file, this->m_files)
    {
        Application* app = new Application(file);
        // qDebug() << "Found application: " << app->name();
        emit appFound(app);
    }
    this->m_files.clear();
}

QStringList ApplicationFinder::readFolder(QString folder)
{
    QDir dir(folder);
    QFileInfoList file_list = dir.entryInfoList(QStringList(APPLICATIONS_FILES), QDir::Files | QDir::Readable);
    QStringList files;
    foreach(QFileInfo file, file_list)
        if (this->m_files.filter(file.fileName()).count() == 0)
            files.append(file.absoluteFilePath());
    return files;
}

ApplicationFinder::ApplicationFinder(QObject *parent) :
    QObject(parent)
{}

ApplicationFinder::~ApplicationFinder()
{
    if (m_thread.isRunning())
        m_thread.cancel();
    m_files.clear();
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
