#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

signals:

public slots:
};

#endif // REPOSITORY_H