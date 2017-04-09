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
    std::vector<QString> pattern;
};

#endif // GCODESSYNTAXHIGHLIGHTER_H
