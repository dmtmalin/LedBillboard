#include <QString>
#include <QUrl>
#include <QIODevice>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QApplication>
#include <QDebug>
#include <QUuid>
#include "utils.h"

Utils::Utils()
{

}

QString Utils::getFileName(const QUrl &url, const QString prefix)
{
    QString path = url.path();
    QString name = QFileInfo(path).fileName();
    if (name.isEmpty()) {
        name = "media." + getUuid();
        qWarning() << QString("Could not get filename from %1. Generate name: %2").arg(path, name);
    }
    QString filepath = QApplication::applicationDirPath() + QDir::separator();
    if(!prefix.isEmpty()) {
        filepath += prefix + QDir::separator();
    }
    if(!QDir(filepath).exists()) {
        QDir().mkdir(filepath);
    }
    return QDir::cleanPath(filepath + name);
}

bool Utils::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << QString("Could not open %1 for writing: %2.").arg(
                          filename, file.errorString());
        return false;
    }
    file.write(data->readAll());
    file.close();
    return true;
}

QString Utils::getUuid()
{
    QString uuid = QUuid::createUuid().toString();
    return uuid
            .remove(uuid.count() - 1, 1)
            .remove(0, 1);
}
