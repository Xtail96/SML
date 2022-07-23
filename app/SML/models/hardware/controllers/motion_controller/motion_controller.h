#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include <QObject>

#include "../base_controller.h"
#include "./motion_controller_repository.h"

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

    void processTask(Task t) override;

    void stopProcessing() override;

private:
    const QString m_controllerName = "motionController";

    QList<QMetaObject::Connection> m_slotsInfo;

    MotionControllerRepository m_repository;

    void onClientConnected(QtJson::JsonObject initialState) override;

    void newMessageHandler(QtJson::JsonObject msg) override;

signals:
    void positionChanged();

    friend class HardwareDriver;
};

#endif // MOTIONCONTROLLER_H
