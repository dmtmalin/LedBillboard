#ifndef UTILS_H
#define UTILS_H

class QString;
class QUrl;
class QIODevice;

class Utils
{
public:
    Utils();
    static QString getFileName(const QUrl &url, const QString prefix="");
    static bool saveToDisk(const QString &filename, QIODevice *data);
    static QString getUuid();
};

#endif // UTILS_H
