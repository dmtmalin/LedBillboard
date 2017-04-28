#ifndef UTILS_H
#define UTILS_H

class QString;
class QUrl;
class QIODevice;

class Utils
{
public:
    Utils();
    /**
     * @brief getFileName получение полного имени файла из Url.
     * @param url адрес.
     * @param prefix имя директории для сохранения.
     * @return полное имя файла.
     */
    static QString getFileName(const QUrl &url, const QString prefix="");
    /**
     * @brief saveToDisk сохранение данных в файл.
     * @param filename полное имя файла.
     * @param data данные.
     * @return
     */
    static bool saveToDisk(const QString &filename, QIODevice *data);
    /**
     * @brief getUuid получение уникального UUID.
     * @return UUID.
     */
    static QString getUuid();
};

#endif // UTILS_H
