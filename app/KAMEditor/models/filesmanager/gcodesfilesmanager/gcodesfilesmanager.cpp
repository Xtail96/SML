#include "gcodesfilesmanager.h"

GCodesFilesManager::GCodesFilesManager(QObject *parent) :
    QObject(parent),
    filePath(""),
    fileContent(QStringList())
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
    //fileContent = readFileInfo(path);
    fileContent = readFileInfo(path);
}

QStringList GCodesFilesManager::readFileInfo(QString path)
{
    QStringList content = QStringList();

    /*QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);
        content = in.readAll();
        inputFile.close();
    }*/

    QTime time;
    time.start();

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox(QMessageBox::Warning, "Ошибка", ("Невозможно открыть файл:\n"+ path));
    }
    else
    {
        // Prepare text stream
        QTextStream textStream(&file);

        // Read lines
        while (!textStream.atEnd())
        {
            content.append(textStream.readLine());
        }
    }
    return content;
}

QString GCodesFilesManager::loadFile(QString path)
{
    QTime time;
    time.start();

    QString content = "";

    QStringList data;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox(QMessageBox::Warning, "Ошибка", ("Невозможно открыть файл:\n"+ path));
    }
    else
    {
        // Prepare text stream
        QTextStream textStream(&file);

        // Read lines
        while (!textStream.atEnd())
        {
            data.append(textStream.readLine());
        }
    }

    qDebug() << "Prepared to load:" << time.elapsed();
    time.start();

    double currentValue = 0;
    double progressStep = ((double) (100)) / ((double) (data.count()));

    //emit startLoading();

    for(auto line : data)
    {
        content += line + QString('\n');
        currentValue += progressStep;
        qDebug() << currentValue << progressStep;
        //emit loading(currentValue);
    }

    //emit loaded();
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
            QString data;
            for(auto line : fileContent)
            {
                data.append(line + '\n');
            }
            file.write(data.toUtf8());
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
    setFileContent(QStringList());
}

void GCodesFilesManager::addGCodesFile()
{
    QString originPath = filePath;
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
    QStringList content = readFileInfo(path);
    if(content.size() > 0)
    {
        fileContent += content;
    }
    filePath = originPath;
}

QStringList GCodesFilesManager::getContent() const
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

void GCodesFilesManager::setFileContent(const QStringList &value)
{
    fileContent = value;
}

