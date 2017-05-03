#ifndef MEDIACONTENT_H
#define MEDIACONTENT_H

namespace Model {
class MediaContent;
}

class QString;
class QJsonObject;

class MediaContent
{
public:
    MediaContent();
    /**
     * @brief fromJson создание объекта из JSON.
     * @param obj объект JSON.
     * @return указатель на объект.
     */
    static MediaContent* fromJson(QJsonObject &obj);
    void setId(int &id);
    void setUrl(QString &url);
    void setFileName(QString &fileName);
    int getId();
    QString getUrl();
    QString getFileName();

private:
    /**
     * @brief id внутренний id.
     */
    int id;
    /**
     * @brief url ссылка на файл.
     */
    QString url;
    /**
     * @brief fileName полное имя файла (путь).
     */
    QString fileName;
};

#endif // MEDIACONTENT_H
