#include <QApplication>
#include <QSettings>
#include <QMetaEnum>
#include <QStringList>
#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    QString app_dir = QApplication::applicationDirPath();
    QString settings_path = app_dir + "/settings.ini";
    settings = new QSettings(settings_path, QSettings::IniFormat);
    this->setDefaultValue(Settings::HOST, "http://127.0.0.1:8000");
    this->setDefaultValue(Settings::USERNAME, "admin@admin.com");
    this->setDefaultValue(Settings::PASSWORD, "adminAdmin");
    this->setDefaultValue(Settings::BOARD, "defaultBoard");    
    this->setDefaultValue(Settings::RETRY, 60000);
    this->setDefaultValue(Settings::SCREEN, 0);
    this->settings->sync();
}

QString Settings::getValue(Settings::Key key)
{
    QString metaKey = this->toMetaKey(key);
    QString value = settings->value(metaKey).toString();
    return value;
}

void Settings::setValue(Settings::Key key, QVariant value)
{
    QString metaKey = this->toMetaKey(key);
    settings->setValue(metaKey, value);
}

QString Settings::toMetaKey(Settings::Key key)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<Settings::Key>();
    QString metaKey = metaEnum.valueToKey(key);
    return metaKey;
}

void Settings::setDefaultValue(Settings::Key key, QVariant value)
{
    QStringList keys = settings->allKeys();
    QString metaKey = this->toMetaKey(key);
    bool isContains = keys.contains(metaKey, Qt::CaseInsensitive);
    if (!isContains) {
        this->setValue(key, value);
    }
}

Settings::~Settings()
{
    delete this->settings;
}
