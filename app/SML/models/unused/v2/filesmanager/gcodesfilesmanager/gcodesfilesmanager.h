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

#include "models/filesmanager/gcodesfilesmanager/filesreader.h"

class GCodesFilesManager : public QObject
{
    Q_OBJECT
protected:
    QString filePath;
    QString fileContent;

    QThread* m_readerThread;

public:
    GCodesFilesManager(QObject *parent);
    ~GCodesFilesManager();

    void openGCodesFile();
    void openGCodesFile(QString path);
    void readFileInfo(QString path);
    void saveGCodesFile();
    void saveGCodesFileAs();
    static void createGCodesFile(const QString path);
    void newGCodesFile();
    void addGCodesFile();

    QString getContent() const;
    QString getFilePath() const;
    void setFilePath(const QString &value);
    void setFileContent(const QString &value);

signals:
    void loadedFile();

public slots:
    void onFileLoaded(QString content);
};

#endif // GCODESFILESMANAGER_H
