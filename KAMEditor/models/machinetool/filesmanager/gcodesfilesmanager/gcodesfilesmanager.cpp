#include "gcodesfilesmanager.h"

GCodesFilesManager::GCodesFilesManager() :
    filePath(""),
    content("")
{

}

void GCodesFilesManager::openFile()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.7kam");
    openFile(path);
}

void GCodesFilesManager::openFile(QString path)
{
    filePath = path;
    content = readFileInfo(path);
}

QString GCodesFilesManager::readFileInfo(QString path)
{
    QString content = "";
    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        filePath = path;
        QTextStream in(&inputFile);
        content = in.readAll();
        inputFile.close();
    }
    return content;
}

QString GCodesFilesManager::getContent() const
{
    return content;
}

QString GCodesFilesManager::getFilePath() const
{
    return filePath;
}

void GCodesFilesManager::setFilePath(const QString &value)
{
    filePath = value;
}
