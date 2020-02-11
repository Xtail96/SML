#include <QApplication>
#include <QCommandLineParser>
#include <QRegularExpression>
#include <widget/candle_visualizer_dialog.h>
#include <QDebug>

QRegularExpression lineSeparator()
{
    return QRegularExpression{R"-((\r\n?|\n))-"};
}

QStringList readFromFile(QString path)
{
    QStringList result = {};
    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);
        QString content = in.readAll();
        inputFile.close();

        result = content.split(lineSeparator());
    }

    return result;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("CandleGCodesViewer");
    QApplication::setApplicationVersion("0.0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Display GCodes as 3d-scene using candle project widget");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption fileOption({"f", "file"}, "get gcodes from file", "file", "");
    parser.addOption(fileOption);

    QCommandLineOption inlineOption({"i", "inline"}, "get gcodes from command line", "inline", "");
    parser.addOption(inlineOption);

    parser.process(a);

    QStringList gcodes = {};
    if(parser.isSet(fileOption))
    {
       gcodes = readFromFile(parser.value(fileOption));
    }
    else if(parser.isSet(inlineOption))
    {
        gcodes = parser.value(inlineOption).split(lineSeparator());
    }

    if(gcodes.length() < 0)
    {
        return 0;
    }

    CandleVisualizerDialog(gcodes, nullptr).exec();

    return a.exec();
}
