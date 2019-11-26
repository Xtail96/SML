#ifndef GCODESFILESMANAGER_H
#define GCODESFILESMANAGER_H

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QProgressDialog>
#include <QTime>
#include <QThread>
#include <QProgressDialog>
#include <QRegularExpression>

#include "models/machine_tool_elements/gcodes/file_reader/file_reader.h"

class GCodesFileManager : public QObject
{
    Q_OBJECT
protected:
    QString m_filePath;
    QStringList m_fileContent;

    QThread* m_readerThread;

public:
    GCodesFileManager(QObject *parent);
    ~GCodesFileManager();

    void openGCodesFile();
    void openGCodesFile(QString path);
    void readFileInfo(QString path);
    void saveGCodesFile();
    void saveGCodesFileAs();
    static void createGCodesFile(const QString path);
    void newGCodesFile();
    void addGCodesFile();

    QStringList getContent() const;
    QString getFilePath() const;
    void setFilePath(const QString &value);
    void setFileContent(const QString &value);

signals:
    void loadedFile();

    void filePathUpdated(QString path);
    void fileContentUpdated(QStringList data);

public slots:
    void onFileLoaded(QString content);
};

#endif // GCODESFILESMANAGER_H
