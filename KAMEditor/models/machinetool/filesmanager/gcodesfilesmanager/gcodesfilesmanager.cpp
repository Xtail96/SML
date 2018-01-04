#include "gcodesfilesmanager.h"

GCodesFilesManager::GCodesFilesManager()
{

}

void GCodesFilesManager::openGCodesFile()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
    if(path.length() > 0)
    {
        openGCodesFile(path);
    }
}

void GCodesFilesManager::openGCodesFile(QString path)
{
    filePath = path;
    fileContent = readFileInfo(path);
}

QString GCodesFilesManager::readFileInfo(QString path)
{
    QString content = "";
    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);
        content = in.readAll();
        inputFile.close();
    }
    return content;
}

QString GCodesFilesManager::getContent() const
{
    return fileContent;
}

QString GCodesFilesManager::getFilePath() const
{
    return filePath;
}

void GCodesFilesManager::setFilePath(const QString &value)
{
    filePath = value;
}
