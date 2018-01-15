#include "gcodeswebviewdialog.h"
#include "ui_gcodeswebviewdialog.h"

GCodesWebViewDialog::GCodesWebViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCodesWebViewDialog)
{
    ui->setupUi(this);

    QWebEngineView *engine_view = new QWebEngineView(ui->frame);
    engine_view->setAcceptDrops(true);
    engine_view->setEnabled(true);
    connect(engine_view, SIGNAL(loadFinished(bool)), engine_view, SLOT(show()));

    engine_view->load(QUrl("http://jherrm.com/gcode-viewer/"));
    //engine_view->load(QUrl("file:///Users/Xtail/Projects/SML-Qt/KAMEditor/gui/web/index.html"));
    //engine_view->load(QUrl("file:///Users/Xtail/Projects/GCodesViewer/gcode-viewer-master_/web/index.html"));
    //engine_view->load(QUrl("qrc:///web/index.html"));

    //
    //engine_view->show();
    //connect(engine_view, SIGNAL(loadStarted()), this, SLOT(showDownloadProgress()));
    //connect(engine_view, SIGNAL(loadFinished(bool)), this, SLOT(stopDownload()));
}

GCodesWebViewDialog::~GCodesWebViewDialog()
{
    delete ui;
}
