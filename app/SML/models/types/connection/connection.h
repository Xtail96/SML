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

    int lastError() const;
    void setLastError(int lastError);

protected:
    bool m_connected;
    int m_lastError;

signals:
    void connectionStateChanged(bool connected);
    void lastErrorChanged(int lastError);

public slots:
};

#endif // CONNECTION_H
