#ifndef GCODESEDITORWIDGET_H
#define GCODESEDITORWIDGET_H

#include <QObject>
#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

class GCodesEditorWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    GCodesEditorWidget(QWidget *parent = 0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(GCodesEditorWidget *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    GCodesEditorWidget *codeEditor;
};

#endif // GCODESEDITORWIDGET_H
