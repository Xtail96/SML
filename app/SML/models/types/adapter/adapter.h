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

    int workflowState() const;
    void setWorkflowState(int workflowState);

    int errorCode() const;
    void setErrorCode(int errorCode);

protected:
    bool m_connected;
    int m_workflowState;
    int m_errorCode;

signals:
    void connectionStateChanged(bool connected);
    void workflowStateChanged(int state);
    void errorIsOccured(int errorCode);

public slots:
};

#endif // CONNECTION_H
