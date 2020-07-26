#ifndef FILESREADER_H
#define FILESREADER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);

    void readFileInfo(QString path);

signals:
    void successfullRead(QString content);
    void loading(int line);

public slots:
};

#endif // FILESREADER_H
