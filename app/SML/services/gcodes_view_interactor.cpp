#include "gcodes_view_interactor.h"

GCodesViewInteractor::GCodesViewInteractor()
{

}

void GCodesViewInteractor::execute(QStringList gcodes, QObject* parent)
{
    QStringList args = {"-i", gcodes.join("\r\n")};
    QProcess* viewProcess = new QProcess(parent);
    QObject::connect(viewProcess, SIGNAL(finished(int)), viewProcess, SLOT(deleteLater()));
    viewProcess->start(getViewerPath(), args);
}

void GCodesViewInteractor::execute(QString gcodesFileName, QObject* parent)
{
    QStringList args = {"-f", gcodesFileName};
    QProcess* viewProcess = new QProcess(parent);
    QObject::connect(viewProcess, SIGNAL(finished(int)), viewProcess, SLOT(deleteLater()));
    viewProcess->start(getViewerPath(), args);
}

QString GCodesViewInteractor::getViewerPath()
{
    QString gcodesViewerPath = "";

    SettingsManager s = SettingsManager();
    gcodesViewerPath = s.get("ExternalTools", "GCodesViewer").toString();

    return gcodesViewerPath;
}
