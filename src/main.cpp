#include <QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <QApplication>
#include <VLCQtCore/Common.h>
#include "gui/mainwindow.h"

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message;
    switch (type) {
        case QtInfoMsg:
            message = QString("Info: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
            break;
        case QtDebugMsg:
            message = QString("Debug: %1 (%2:%4, %4)").arg(msg, context.file, QString::number(context.line), context.function);
            break;
        case QtWarningMsg:
            message = QString("Warning: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
            break;
        case QtCriticalMsg:
            message = QString("Critical: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
            break;
        case QtFatalMsg:
            message = QString("Fatal: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
            break;
        default:
            message = QString("%1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
            break;
    }
    QString app_dir = QApplication::applicationDirPath();
    QFile outFile(app_dir + "/app.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << message << endl;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
    QCoreApplication::setApplicationName("LedBillboard");
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

    QApplication app(argc, argv);
    VlcCommon::setPluginPath(app.applicationDirPath() + "/plugins");

    MainWindow w;
    w.show();

    return app.exec();
}
