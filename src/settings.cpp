#include <QApplication>
#include <QSettings>
#include <QString>
#include <QVariant>
#include <QMetaEnum>
#include <QStringList>
#include <QDebug>
#include "settings.h"

const char* DEFAULT_HOST =  "http://127.0.0.1:8000";
const char* DEFAULT_USERNAME =  "a@a.com";
const char* DEFALT_PASSWORD =  "Pw123456";

Settings::Settings(QObject *parent) : QObject(parent)
{
    QString app_dir = QApplication::applicationDirPath();
    QString settings_path = app_dir + "/settings.ini";
    settings = new QSettings(settings_path, QSettings::IniFormat);
    this->setDefaultValue(Settings::HOST, DEFAULT_HOST);
    this->setDefaultValue(Settings::USERNAME, DEFAULT_USERNAME);
    this->setDefaultValue(Settings::PASSWORD, DEFALT_PASSWORD);
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
