#ifndef MEDIACONTENT_H
#define MEDIACONTENT_H

namespace Model {
class MediaContent;
}

class QString;
class QJsonObject;

/*
 * Объект медиа файла.
 * Методы:
 *  fromJson - создание объекта из JSON.
 * Свойства:
 *  id - внутренний id.
 *  url - ссылка на файл.
 *  fileName - полное имя файла (путь).
*/
class MediaContent
{
public:
    MediaContent();
    static MediaContent* fromJson(QJsonObject &obj);
    void setId(QString &id);
    void setUrl(QString &url);
    void setFileName(QString &fileName);
    QString getId();
    QString getUrl();
    QString getFileName();

private:
    QString id;
    QString url;
    QString fileName;
};

#endif // MEDIACONTENT_H
