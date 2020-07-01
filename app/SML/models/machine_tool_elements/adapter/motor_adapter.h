#ifndef MOTORADAPTER_H
#define MOTORADAPTER_H

#include <QObject>
#include <QWebSocket>

class MotorAdapter : public QObject
{
    Q_OBJECT
public:
    explicit MotorAdapter(QObject *parent = nullptr);
    ~MotorAdapter();

private:

signals:

};

#endif // MOTORADAPTER_H
