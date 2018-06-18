#include "filesreader.h"

FilesReader::FilesReader(QObject *parent) : QObject(parent)
{

}

void FilesReader::readFileInfo(QString path)
{
    QString content = "";

    int linesCount = 0;

    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!inputFile.atEnd())
        {
            content += inputFile.readLine();
            linesCount++;
            emit loading(linesCount);
        }
        emit successfullRead(content);

        //QTextStream in(&inputFile);
        //content = in.readAll();
        //inputFile.close();
    }
}
