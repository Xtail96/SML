#ifndef GCODESSYNTAXHIGHLIGHTER_H
#define GCODESSYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QString>
#include <QRegExp>
#include <vector>


class GCodesSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    GCodesSyntaxHighlighter(QObject *parent);
    void highlightBlock(const QString &text);
    void setPattern();
private:
    QList<QString> gPattern;
    QList<QString> mPattern;
    QList<QString> argumentsPattern;
    QList<QString> commentsPattern;

    void setHighlightColor(const QString &text, QList<QString> pattern, const QBrush &brush);

};

#endif // GCODESSYNTAXHIGHLIGHTER_H
