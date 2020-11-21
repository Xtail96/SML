#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include <QObject>

#include "libs/json_parser/json.h"

#include "../base_controller.h"

#include "./axis/axis.h"

/**
 * @brief Контроллер двигаталей.
 */
class MotionController : public BaseController
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса.
     * @param parent - родительский объект
     */
    explicit MotionController(QObject *parent = nullptr);

    /**
     * @brief Деструктор класса.
     */
    ~MotionController() override;

    bool axisExists(AxisId id);
    void addAxis(AxisId id, double initialPosition);
    void removeAxis(AxisId id);
    void clearAxes();

    //void moveTo(Point absPos);
    //void moveOffset(Point relPos);

    //void executeChunk(QString gcode);

    //void stopMoving();

private:
    /// Доступные оси станка.
    QSet<Axis*> m_axes;
    QList<QMetaObject::Connection> m_slotsInfo;

    void setup(QtJson::JsonObject initialState) override;

    void newMessageHandler(QtJson::JsonObject msg) override;

    Axis* findById(AxisId id);
};

#endif // MOTIONCONTROLLER_H
