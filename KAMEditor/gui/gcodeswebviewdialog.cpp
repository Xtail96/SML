#include "gcodeswebviewdialog.h"
#include "ui_gcodeswebviewdialog.h"

GCodesWebViewDialog::GCodesWebViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCodesWebViewDialog)
{
    ui->setupUi(this);
    engine_view = new QWebEngineView(ui->frame);

    // enable XMLHttpRequest
    //engine_view->settings()->setAttribute(QWebEngineSettings::XSSAuditingEnabled, false);

    connect(engine_view, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(reset()));
    connect(engine_view, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));
    connect(engine_view, SIGNAL(loadFinished(bool)), engine_view, SLOT(show()));
    engine_view->load(QUrl("qrc:///web/index.html?path=123"));
}

GCodesWebViewDialog::~GCodesWebViewDialog()
{
    delete engine_view;
    delete ui;
}
