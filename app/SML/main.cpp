#include <QApplication>
#include "gui/mainwindow.h"

#include <QDateTime>

static QString APP_DIR = ".";

void myMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{
    QString txt;
    static long long uid=0; //-- номеруем вывод
    //-- название функции с классом, берём только класс и саму функцию
    QRegExp rx("([\\w-]+::[\\w-]+)");
    if (rx.indexIn(context.function) ==-1) return;
    QString function = rx.cap(1);

    QString msgSep = (msg.length()>0)? ">> " : "";

    switch (type) {
        case QtInfoMsg:
            txt = QString("Info: %1%2%3").arg(function).arg(msgSep).arg(msg);
        break;
        case QtDebugMsg:
            txt = QString("Debug: %1%2%3").arg(function).arg(msgSep).arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning: %1%2%3").arg(function).arg(msgSep).arg(msg);
        break;
        case QtCriticalMsg:
            txt = QString("Critical: %1%2%3").arg(function).arg(msgSep).arg(msg);
        break;
        case QtFatalMsg:
            txt = QString("Fatal: %1%2%3").arg(function).arg(msgSep).arg(msg);
            abort();
    }

    QDateTime dateTime = QDateTime::currentDateTime();
    uid++;
    txt=QString("%1:%2 %3").arg(dateTime.toString(Qt::ISODate)).arg(uid).arg(txt);

    QFile outFile(QString("%1/log-%2.log").arg(APP_DIR).arg(QDate::currentDate().toString("dd.MM.yy")));

    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
    outFile.close();

    qDebug() << txt;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    APP_DIR = qApp->applicationDirPath();
    qInstallMessageHandler(myMessageHandler);

    QCoreApplication::setApplicationName("SML");

    MainWindow w;
    w.show();

    return a.exec();
}
