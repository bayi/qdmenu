#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
public:
    Settings(QObject* parent = 0);
    virtual ~Settings();

    Q_INVOKABLE
    QVariant get(const QString &key, const QVariant &def);

    Q_INVOKABLE
    qreal getNumber(const QString &key, const QVariant &def);

    Q_INVOKABLE
    bool getBool(const QString &key, const QVariant &def);

    Q_INVOKABLE
    void initDefaults(void);

private:
    void checkAndSet(const QString &key, const QVariant &val);
};

#endif // SETTINGS_H
