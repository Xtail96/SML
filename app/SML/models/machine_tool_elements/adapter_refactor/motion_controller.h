#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include <QObject>
#include "libs/json_parser/json.h"

#include "models/machine_tool_elements/adapter_refactor/base_controller.h"

#include "models/machine_tool_elements/axis/axis.h"
#include "models/machine_tool_elements/point/point.h"

class MotionController : public BaseController
{
    Q_OBJECT
public:
    explicit MotionController(QObject *parent = nullptr);
    ~MotionController() override;

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

#endif // MOTIONCONTROLLER_H
