#ifndef GCODESWEBVIEWDIALOG_H
#define GCODESWEBVIEWDIALOG_H

#include <QDialog>
#include <QWebEngineView>
#include <QWebEngineSettings>

namespace Ui {
class GCodesWebViewDialog;
}

class GCodesWebViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GCodesWebViewDialog(QWidget *parent = 0);
    ~GCodesWebViewDialog();
private slots:

private:
    Ui::GCodesWebViewDialog *ui;
    QWebEngineView *engine_view;
};

#endif // GCODESWEBVIEWDIALOG_H
