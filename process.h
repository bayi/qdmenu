#ifndef PROESS_H
#define PROESS_H

#include <QObject>
#include "desktopfile.h"

/**
 * @brief The Process class
 *
 * Starts an application in a new process and quits
 */
class Process : public QObject
{
    Q_OBJECT
public:
    explicit Process(QObject *parent = 0);

    Q_INVOKABLE void start(QString program, bool isTerm = false);

signals:

public slots:
};

#endif // PROESS_H
