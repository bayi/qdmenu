#include "process.h"
#include <QProcess>

Process::Process(QObject *parent) : QObject(parent)
{}

void Process::start(QString program, bool isTerm)
{
    // Remove parameters
    QString command = program.remove(QRegExp("%[a-zA-Z]")).trimmed();

    if (isTerm)
    {
        QProcess::startDetached("qdmenu-terminal", QStringList() << "-e" << command);
    } else {
        QProcess::startDetached(command);
    }

    // Bye bye...
    exit(0);
}
