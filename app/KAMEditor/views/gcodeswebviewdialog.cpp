#include "gcodeswebviewdialog.h"
#include "ui_gcodeswebviewdialog.h"

GCodesWebViewDialog::GCodesWebViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCodesWebViewDialog)
{
    ui->setupUi(this);

#ifdef Q_OS_UNIX
    engine_view = new QWebEngineView(ui->webEngineFrame);
    connect(engine_view, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(reset()));
    connect(engine_view, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));
    connect(engine_view, SIGNAL(loadFinished(bool)), engine_view, SLOT(show()));
    engine_view->load(QUrl("qrc:///web/index.html"));
#endif
}

GCodesWebViewDialog::~GCodesWebViewDialog()
{
#ifdef Q_OS_UNIX
    delete engine_view;
#endif
    delete ui;
}
