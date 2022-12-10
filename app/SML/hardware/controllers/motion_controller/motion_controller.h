#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include <QObject>

#include "../base_controller.h"
#include "./axes_repository.h"

/**
 * @brief Контроллер двигаталей.
 */
class MotionController : public BaseController
{
    Q_OBJECT
public:
    explicit MotionController(QObject *parent = nullptr);
    ~MotionController() override;
    void processTask(Task t) override;
    void stopProcessing() override;
    void onClientConnected(QtJson::JsonObject initialState) override;
    void onMessageReceived(QtJson::JsonObject msg) override;
    void onDisconnected() override;
private:
    const QString m_controllerName = "motionController";
    AxesRepository m_repository;
signals:
    void positionChanged();
friend class HardwareDriver;
};

#endif // MOTIONCONTROLLER_H
