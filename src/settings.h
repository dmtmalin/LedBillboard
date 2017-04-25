#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QMetaEnum>
#include "singleton.h"

extern const char* DEFAULT_HOST;
extern const char* DEFAULT_USERNAME;
extern const char* DEFALT_PASSWORD;
extern const char* DEFAULT_BOARD;

class QSettings;
class QString;
class QVariant;

class Settings : public QObject
{
    Q_OBJECT
public:
    enum Key {
        HOST,
        USERNAME,
        PASSWORD,
        BOARD
    };
    Q_ENUM(Key)
    explicit Settings(QObject *parent = 0);
    ~Settings();

    QString getValue(Settings::Key key);
    void setValue(Settings::Key key, QVariant value);

private:

    QString toMetaKey(Settings::Key key);
    void setDefaultValue(Settings::Key key, QVariant value);

    QSettings *settings;
};

typedef Singleton<Settings> settings;

#endif // SETTINGS_H
