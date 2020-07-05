#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include <QObject>
#include "libs/json_parser/json.h"

#include "models/machine_tool_elements/adapter_refactor/base_controller.h"

#include "models/machine_tool_elements/axis/axis.h"
#include "models/machine_tool_elements/point/point.h"

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

    /**
     * @brief Возвращает текущее положение станка относительно базы.
     * @return Текущее положение станка в абсолютных координатах.
     */
    Point currentPos();

    //void moveTo(Point absPos);
    //void moveOffset(Point relPos);

    //void executeChunk(QString gcode);

    //void stopMoving();

private:
    /// Доступные оси станка.
    QSet<Axis*> m_axes;

    /**
     * @brief Устанавливает текущее положение станка относительно базы.
     * @param absPos - обновленное положение станка относительно базы.
     */
    void setCurrentPos(Point absPos);

    /**
     * @brief Обработчик сообщения от адаптера в виде массива байт.
     * @param message - принятое сообщение от адаптера
     */
    void parseBinaryMessage(QByteArray message) override;

    /**
     * @brief Обработчик сообщения от адаптера в виде текста.
     * @param message - принятое сообщение от адаптера
     */
    void parseTextMessage(QString message) override;

signals:

};

#endif // MOTIONCONTROLLER_H
