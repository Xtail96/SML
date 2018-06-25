#include "gcodesfilesmanager.h"

GCodesFilesManager::GCodesFilesManager(QObject *parent) :
    QObject(parent),
    m_filePath(""),
    m_fileContent(""),
    m_readerThread(new QThread(this))
{
    m_readerThread->setObjectName("ReaderThread");
}

GCodesFilesManager::~GCodesFilesManager()
{
    if(m_readerThread->isRunning())
    {
        m_readerThread->quit();
        m_readerThread->wait();
    }
    delete m_readerThread;
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
    m_filePath = path;
    readFileInfo(path);
}

void GCodesFilesManager::readFileInfo(QString path)
{
    FilesReader* reader = new FilesReader();
    reader->moveToThread(m_readerThread);
    connect(m_readerThread, SIGNAL(finished()), reader, SLOT(deleteLater()));
    connect(reader, SIGNAL(successfullRead(QString)), this, SLOT(onFileLoaded(QString)));

    QProgressDialog* progressDialog = new QProgressDialog("Opening file. Please wait", "", 0, 100);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setFixedSize(progressDialog->sizeHint());
    progressDialog->setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");

    connect(m_readerThread, SIGNAL(started()), progressDialog, SLOT(show()));
    connect(m_readerThread, SIGNAL(finished()), progressDialog, SLOT(deleteLater()));
    connect(reader, SIGNAL(loading(int)), progressDialog, SLOT(setValue(int)));

    m_readerThread->start();
    reader->readFileInfo(path);
}

void GCodesFilesManager::saveGCodesFile()
{

    if(QFileInfo::exists(m_filePath))
    {
        QFile file(m_filePath);

        if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу открыть файл!").exec();
        }
        else
        {
            file.write(m_fileContent.toUtf8());
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
            m_filePath = filename;
            saveGCodesFile();
            openGCodesFile(m_filePath);
        }
        else
        {
            m_filePath = "";
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

    emit filePathUpdated(m_filePath);
    emit fileContentUpdated(m_fileContent);
}

void GCodesFilesManager::addGCodesFile()
{
    /*QString originPath = filePath;
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");

    QString content = readFileInfo(path);
    if(content.size() > 0)
    {
        fileContent += content;
    }
    filePath = originPath;*/
}

QString GCodesFilesManager::getContent() const
{
    return m_fileContent;
}

QString GCodesFilesManager::getFilePath() const
{
    return m_filePath;
}

void GCodesFilesManager::setFilePath(const QString &value)
{
    m_filePath = value;
}

void GCodesFilesManager::setFileContent(const QString &value)
{
    m_fileContent = value;
}

void GCodesFilesManager::onFileLoaded(QString content)
{
    m_fileContent = content;
    m_readerThread->quit();
    m_readerThread->wait();
    qDebug() << "gcodes file loaded";
    emit filePathUpdated(m_filePath);
    emit fileContentUpdated(m_fileContent);
}

