#ifndef MOTORADAPTER_H
#define MOTORADAPTER_H

#include <QObject>
#include "libs/json_parser/json.h"

#include "models/machine_tool_elements/adapter/base_adapter.h"

#include "models/machine_tool_elements/axis/axis.h"
#include "models/machine_tool_elements/point/point.h"

class MotorAdapter : public BaseAdapter
{
    Q_OBJECT
public:
    explicit MotorAdapter(QObject *parent = nullptr);
    ~MotorAdapter();

    Point currentPos();
    void setCurrentPos(Point absPos);

    //void moveTo(Point absPos);
    //void moveOffset(Point relPos);

    //void executeChunk(QString gcode);

    //void stopMoving();

private:
    QSet<Axis*> m_axes;

    void parseBinaryMessage(QByteArray message) override;
    void parseTextMessage(QString message) override;

signals:

};

#endif // MOTORADAPTER_H
