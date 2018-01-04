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

    QString getContent() const;
    QString getFilePath() const;
    void setFilePath(const QString &value);
};

#endif // GCODESFILESMANAGER_H
