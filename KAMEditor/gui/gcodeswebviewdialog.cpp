#include "gcodeswebviewdialog.h"
#include "ui_gcodeswebviewdialog.h"

GCodesWebViewDialog::GCodesWebViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCodesWebViewDialog)
{
    ui->setupUi(this);
    visualizeThread = new QThread();

    engine_view = new QWebEngineView();
    engine_view->page()->moveToThread(visualizeThread);
    connect(visualizeThread, &QThread::finished, engine_view->page(), &QObject::deleteLater);
    visualizeThread->start();

    //qDebug() << engine_view->thread();
    engine_view->settings()->setAttribute(QWebEngineSettings::XSSAuditingEnabled, false);

    //engine_view->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    //engine_view->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    //engine_view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    //engine_view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    connect(engine_view, SIGNAL(loadStarted()), ui->loadProgressBar, SLOT(reset()));
    connect(engine_view, SIGNAL(loadProgress(int)), ui->loadProgressBar, SLOT(setValue(int)));
    connect(engine_view, SIGNAL(loadFinished(bool)), engine_view, SLOT(show()));
    engine_view->load(QUrl("qrc:///web/index.html?path=123"));
}

GCodesWebViewDialog::~GCodesWebViewDialog()
{
    delete engine_view;
    visualizeThread->quit();
    visualizeThread->wait();
    delete visualizeThread;
    delete ui;
}
