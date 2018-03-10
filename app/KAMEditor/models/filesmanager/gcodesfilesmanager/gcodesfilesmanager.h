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
    QStringList fileContent;
public:
    GCodesFilesManager(QObject *parent);
    void openGCodesFile();
    void openGCodesFile(QString path);
    QStringList readFileInfo(QString path);
    QString loadFile(QString path);
    void saveGCodesFile();
    void saveGCodesFileAs();
    static void createGCodesFile(const QString path);
    void newGCodesFile();
    void addGCodesFile();

    QStringList getContent() const;
    QString getFilePath() const;
    void setFilePath(const QString &value);
    void setFileContent(const QStringList &value);

signals:
    void startLoading();
    void loading(int value);
    void loaded();
};

#endif // GCODESFILESMANAGER_H
