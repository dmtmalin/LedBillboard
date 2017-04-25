#ifndef MEDIACONTENT_H
#define MEDIACONTENT_H

class QString;

class MediaContent
{
public:
    MediaContent();

private:
    QString id;
    QString url;
    QString localFile;
};

#endif // MEDIACONTENT_H
