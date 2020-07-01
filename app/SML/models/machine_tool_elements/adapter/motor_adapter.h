#ifndef MOTORADAPTER_H
#define MOTORADAPTER_H

#include <QObject>
#include <QWebSocket>

#include "models/machine_tool_elements/axis/axis.h"
#include "models/machine_tool_elements/point/point.h"

class MotorAdapter : public QObject
{
    Q_OBJECT
public:
    explicit MotorAdapter(QWebSocket* socket, QObject *parent = nullptr);
    ~MotorAdapter();

    Point currentPos();
    void setCurrentPos(Point absPos);

    void moveTo(Point absPos);
    void moveOffset(Point relPos);

    void executeChunk(QString gcode);

    void stopMoving();
private:
    QScopedPointer<QWebSocket> m_socket;




signals:

private slots:
    qint64 sendMessage(QByteArray message);

};

#endif // MOTORADAPTER_H
