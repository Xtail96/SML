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

void GCodesFilesManager::saveGCodesFile()
{

    if(QFileInfo::exists(filePath))
    {
        QFile file(filePath);

        if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу открыть файл!").exec();
        }
        else
        {
            file.write(fileContent.toUtf8());
            file.close();
        }
    }
    else
    {
        saveGCodesFileAs();
    }
}

void GCodesFilesManager::saveGCodesFileAs()
{
    QString filename = QFileDialog::getSaveFileName(0, "Выберите место сохранения прогрммы", "", "*.txt");
    if(filename.length() > 0)
    {
        createGCodesFile(filename);
        if(QFileInfo::exists(filename))
        {
            filePath = filename;
            saveGCodesFile();
            openGCodesFile(filePath);
        }
        else
        {
            filePath = "";
            QMessageBox(QMessageBox::Warning, "Ошибка", "Файл не удалось создать").exec();
        }
    }
}

void GCodesFilesManager::createGCodesFile(const QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Файл по адресу " + path + "не удалось открыть при создании").exec();
    }
    else
    {
        file.close();
    }
}

void GCodesFilesManager::newGCodesFile()
{
    setFilePath("");
    setFileContent("");
}

void GCodesFilesManager::addGCodesFile()
{
    QString originPath = filePath;
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
    QString content = readFileInfo(path);
    if(content.size() > 0)
    {
        fileContent += content;
    }
    filePath = originPath;
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

void GCodesFilesManager::setFileContent(const QString &value)
{
    fileContent = value;
}

