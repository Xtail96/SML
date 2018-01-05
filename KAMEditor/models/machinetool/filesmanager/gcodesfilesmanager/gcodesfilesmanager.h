#ifndef GCODESFILESMANAGER_H
#define GCODESFILESMANAGER_H

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QDebug>

class GCodesFilesManager
{
protected:
    QString filePath;
    QString fileContent;
public:
    GCodesFilesManager();
    void openGCodesFile();
    void openGCodesFile(QString path);
    QString readFileInfo(QString path);
    void saveGCodesFile();
    void saveGCodesFileAs();
    static void createGCodesFile(const QString path);
    void newGCodesFile();
    void addGCodesFile();

    QString getContent() const;
    QString getFilePath() const;
    void setFilePath(const QString &value);
    void setFileContent(const QString &value);
};

#endif // GCODESFILESMANAGER_H
