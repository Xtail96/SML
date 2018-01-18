#include "gcodeswebviewdialog.h"
#include "ui_gcodeswebviewdialog.h"

GCodesWebViewDialog::GCodesWebViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCodesWebViewDialog)
{
    ui->setupUi(this);

    QWebEngineView *engine_view = new QWebEngineView(ui->frame);
    //engine_view->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    //engine_view->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    //engine_view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    //engine_view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    //engine_view->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    connect(engine_view, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(reset()));
    connect(engine_view, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));
    connect(engine_view, SIGNAL(loadFinished(bool)), engine_view, SLOT(show()));

    engine_view->load(QUrl("qrc:///web/index.html"));
}

GCodesWebViewDialog::~GCodesWebViewDialog()
{
    delete ui;
}
