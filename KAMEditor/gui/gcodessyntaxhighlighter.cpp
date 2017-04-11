#include "gcodessyntaxhighlighter.h"

GCodesSyntaxHighlighter::GCodesSyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{

}



void GCodesSyntaxHighlighter::highlightBlock(const QString &text)
{
    setHighlightColor(text, gPattern, Qt::darkGreen);
    setHighlightColor(text, mPattern, Qt::darkYellow);
    setHighlightColor(text, argumentsPattern, Qt::darkMagenta);
}

void GCodesSyntaxHighlighter::setPattern()
{
    QString g = "G";
    QString m = "M";
    for(int i = 0; i <= 99; i++)
    {
        std::string tmp = std::to_string(i);
        gPattern.push_back(g + QString::fromStdString(tmp) + ':');
        mPattern.push_back(m + QString::fromStdString(tmp) + ':');
    }
    argumentsPattern =
    {
        "X",
        "Y",
        "Z",
        "P",
        "F",
        "S",
        "R",
        "D",
        "L",
        "I",
        "J",
        "K"
    };
}

void GCodesSyntaxHighlighter::setHighlightColor(const QString &text, std::vector<QString> pattern, const QBrush &brush)
{
    QTextCharFormat format;

    for(auto i : pattern)
    {
        QRegExp rx(i);
        if(!rx.isValid() || rx.isEmpty() || rx.exactMatch(""))
        {
            setFormat(0, text.length(), format);
            return;
        }
        format.setForeground(brush);
        int index = rx.indexIn(text);
        while(index >= 0)
        {
            int length = rx.matchedLength();
            setFormat(index, length, format);
            index = rx.indexIn(text, index + length);
        }
    }
}
