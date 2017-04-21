#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QMetaEnum>

extern const char* DEFAULT_HOST;
extern const char* DEFAULT_USERNAME;
extern const char* DEFALT_PASSWORD;

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
        PASSWORD
    };
    Q_ENUM(Key)

    static Settings& Instance() {
        static Settings theSingleInstance;
        return theSingleInstance;
    }
    static QString value(Key key) {
        return Instance().getValue(key);
    }

    QString getValue(Settings::Key key);
    void setValue(Settings::Key key, QVariant value);

private:
    explicit Settings(QObject *parent = 0);
    QString toMetaKey(Settings::Key key);
    void setDefaultValue(Settings::Key key, QVariant value);
    ~Settings();

    QSettings *settings;
};

#endif // SETTINGS_H
