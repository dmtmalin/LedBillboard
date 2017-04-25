#ifndef MEDIACONTENT_H
#define MEDIACONTENT_H

class QString;
class QJsonObject;

class MediaContent
{
public:
    MediaContent();
    static MediaContent fromJson(QJsonObject &obj);
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
