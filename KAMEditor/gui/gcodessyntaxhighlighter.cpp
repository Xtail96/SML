#include "gcodessyntaxhighlighter.h"

GCodesSyntaxHighlighter::GCodesSyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{

}

void GCodesSyntaxHighlighter::highlightBlock(const QString &text)
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
        format.setForeground(Qt::darkGreen);
        int index = rx.indexIn(text);
        while(index >= 0)
        {
            int length = rx.matchedLength();
            setFormat(index, length, format);
            index = rx.indexIn(text, index + length);
        }
    }
}

void GCodesSyntaxHighlighter::setPattern()
{
    pattern =
    {
        "G00:",
        "G01:",
        "G02:",
        "G03:",
        "G04:",
        "G05:",
        "G06:",
        "G07:",
        "G08:",
        "G09:",
        "G10:"
    };
}
