#include "process.h"
#include <QProcess>
#include <qdebug.h>

Process::Process(QObject *parent) : QObject(parent)
{}

void Process::start(QString program, bool isTerm)
{
    // qDebug() << "Executing: " << program;
    QStringList args = QProcess::splitCommand(program);
    QString command = args.takeFirst();
    if (isTerm)
    {
        // qDebug() << "Starting terminal process: " << command << " args: " << args.join(',');
        QProcess::startDetached("qdmenu-terminal", QStringList() << "-e" << command << args);
    } else {
        // qDebug() << "Starting process: " << command << " args: " << args.join(',');
        QProcess::startDetached(command, args);
    }

    // Bye bye...
    exit(0);
}
