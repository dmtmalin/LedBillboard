#include <QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <VLCQtCore/Common.h>
#include "service/apiservice.h"
#include "service/billboardservice.h"
#include "service/playlistcollectionservice.h"
#include "service/timingservice.h"
#include "settings.h"
#include "gui/mainwindow.h"

QFile *logFile;

void releaseLogFile() {
    if (logFile->isOpen()) {
        try {
            logFile->close();
        }
        catch(...) { }
    }
    delete logFile;
}

void releaseResources() {
    delete apiService::Instance();
    delete billboardService::Instance();
    delete playlistCollectionService::Instance();
    delete settings::Instance();
    delete timingService::Instance();

    if (logFile != NULL) {
        releaseLogFile();
    }
}

void logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QString level;
    switch (type) {
        case QtInfoMsg:
            level = "INFO";
            break;
        case QtDebugMsg:
            level = "DEBUG";
            break;
        case QtWarningMsg:
            level = "WARNING";
            break;
        case QtCriticalMsg:
            level = "CRITICAL";
            break;
        case QtFatalMsg:
            level = "FATAL";
            break;
        default:           
            break;
    }
    QDateTime now = QDateTime::currentDateTime();
    QString message = QString("%1 [%2]: %3").arg(now.toString(Qt::ISODateWithMs), level, msg);

    QTextStream ts(logFile);
    ts << message << endl;   
}

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("LedBillboard");
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

    QApplication app(argc, argv);
    VlcCommon::setPluginPath(app.applicationDirPath() + "/plugins");

    QString app_dir = QApplication::applicationDirPath();
    logFile = new QFile(app_dir + "/app.log");
    logFile->open(QIODevice::WriteOnly | QIODevice::Append);

#ifndef QT_DEBUG    
    qInstallMessageHandler(logMessageHandler);
#endif

    qInfo() << "Application is run.";

    MainWindow w;
    w.show();
    try {
        app.exec();
    } catch (const std::bad_alloc &) {
        qCritical() << "Out of memory exception.";
    }
    releaseResources();

    qInfo() << "Application is closed.";
    return 0;
}
