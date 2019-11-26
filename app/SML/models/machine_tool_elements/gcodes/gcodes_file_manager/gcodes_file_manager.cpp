#include "gcodes_file_manager.h"

GCodesFileManager::GCodesFileManager(QObject *parent) :
    QObject(parent),
    m_filePath(""),
    m_fileContent(QStringList{}),
    m_readerThread(new QThread(this))
{
    m_readerThread->setObjectName("ReaderThread");
}

GCodesFileManager::~GCodesFileManager()
{
    if(m_readerThread->isRunning())
    {
        m_readerThread->quit();
        m_readerThread->wait();
    }
    delete m_readerThread;
}

void GCodesFileManager::openGCodesFile()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
    if(path.length() > 0)
    {
        openGCodesFile(path);
    }
}

void GCodesFileManager::openGCodesFile(QString path)
{
    m_filePath = path;
    readFileInfo(path);
}

void GCodesFileManager::readFileInfo(QString path)
{
    FileReader* reader = new FileReader();
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

void GCodesFileManager::saveGCodesFile()
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
            file.write(m_fileContent.join('\n').toUtf8());
            file.close();
        }
    }
    else
    {
        saveGCodesFileAs();
    }
}

void GCodesFileManager::saveGCodesFileAs()
{
    QString filename = QFileDialog::getSaveFileName(0, "Выберите место сохранения прогрммы", "", "*.txt");
    if(filename.length() > 0)
    {
        GCodesFileManager::createGCodesFile(filename);
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

void GCodesFileManager::createGCodesFile(const QString path)
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

void GCodesFileManager::newGCodesFile()
{
    setFilePath("");
    setFileContent("");

    emit filePathUpdated(m_filePath);
    emit fileContentUpdated(m_fileContent);
}

void GCodesFileManager::addGCodesFile()
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

QStringList GCodesFileManager::getContent() const
{
    return m_fileContent;
}

QString GCodesFileManager::getFilePath() const
{
    return m_filePath;
}

void GCodesFileManager::setFilePath(const QString &value)
{
    m_filePath = value;
}

void GCodesFileManager::setFileContent(const QString &value)
{
    m_fileContent = value.split(QRegularExpression{R"-((\r\n?|\n))-"});
}

void GCodesFileManager::onFileLoaded(QString content)
{
    setFileContent(content);
    m_readerThread->quit();
    m_readerThread->wait();
    qDebug() << "gcodes file loaded";
    emit filePathUpdated(m_filePath);
    emit fileContentUpdated(m_fileContent);
}

