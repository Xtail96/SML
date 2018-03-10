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

class GCodesFilesManager : public QObject
{
    Q_OBJECT
protected:
    QString filePath;
    QString fileContent;
public:
    GCodesFilesManager(QObject *parent);
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

signals:
    void startLoading();
    void loading(int value);
    void loaded();
};

#endif // GCODESFILESMANAGER_H
