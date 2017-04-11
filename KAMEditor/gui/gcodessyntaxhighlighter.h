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
    std::vector<QString> gPattern;
    std::vector<QString> mPattern;
    std::vector<QString> argumentsPattern;

    void setHighlightColor(const QString &text, std::vector<QString> pattern, const QBrush &brush);

};

#endif // GCODESSYNTAXHIGHLIGHTER_H
