#ifndef MOTORADAPTER_H
#define MOTORADAPTER_H

#include <QObject>
#include <QWebSocket>
#include "libs/json_parser/json.h"

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
    QMap<QString, Axis> m_axes;
    bool m_workflowState;

    /// Мета-информация о подключенных слотах
    QList<QMetaObject::Connection> m_connections;
    void setupConnections();
    void resetConnections();

signals:

private slots:
    qint64 sendMessage(QByteArray message);

};

#endif // MOTORADAPTER_H
