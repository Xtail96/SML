#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    bool connected() const;
    void setConnected(bool connected);

protected:
    bool m_connected;

signals:
    void connectionStateChanged(bool connected);

public slots:
};

#endif // CONNECTION_H
