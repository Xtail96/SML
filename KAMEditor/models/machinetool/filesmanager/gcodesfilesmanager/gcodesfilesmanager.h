#ifndef GCODESFILESMANAGER_H
#define GCODESFILESMANAGER_H

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>

class GCodesFilesManager
{
protected:
    QString filePath;
    QString content;
public:
    GCodesFilesManager();
    void openFile();
    void openFile(QString path);
    QString readFileInfo(QString path);

    QString getContent() const;
    QString getFilePath() const;
    void setFilePath(const QString &value);
};

#endif // GCODESFILESMANAGER_H
