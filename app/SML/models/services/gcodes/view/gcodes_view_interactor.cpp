#include "gcodes_view_interactor.h"

GCodesViewInteractor::GCodesViewInteractor()
{

}

void GCodesViewInteractor::execute(QStringList gcodes, QObject* parent)
{
    QStringList args = {"-i", gcodes.join("\r\n")};
    auto viewProcess = new QProcess(parent);
    viewProcess->start(getViewerPath(), args);
}

void GCodesViewInteractor::execute(QString gcodesFileName, QObject* parent)
{
    QStringList args = {"-f", gcodesFileName};
    auto viewProcess = new QProcess(parent);
    viewProcess->start(getViewerPath(), args);
}

QString GCodesViewInteractor::getViewerPath()
{
    return "/Users/xtail/Projects/SML/sml-qt/gcodes_viewers/CandleGCodesViewer/app/build-CandleGCodesViewer-Desktop_Qt_5_12_0_clang_64bit-Release/CandleGCodesViewer";
}
