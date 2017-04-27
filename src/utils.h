#ifndef UTILS_H
#define UTILS_H

class QString;
class QUrl;
class QIODevice;

/*
 * Класс утилит.
 * Статические методы:
 *  getFileName - получение полного имени файла из Url.
 *  saveToDisk - сохранение данных в файл.
 *  getUuid - получение уникального UUID.
*/
class Utils
{
public:
    Utils();
    static QString getFileName(const QUrl &url, const QString prefix="");
    static bool saveToDisk(const QString &filename, QIODevice *data);
    static QString getUuid();
};

#endif // UTILS_H
