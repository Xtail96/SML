#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

class Adapter : public QObject
{
    Q_OBJECT
public:
    explicit Adapter(QObject *parent = nullptr);

    bool connected() const;
    void setConnected(bool connected);

protected:
    bool m_connected;

signals:
    void connectionStateChanged(bool connected);

public slots:
};

#endif // CONNECTION_H
