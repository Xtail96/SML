#ifndef HARDWAREDRIVER_H
#define HARDWAREDRIVER_H

#include <QObject>
#include <QQueue>

#include "../common/websockets/websocket_gateway.h"
#include "./controllers/motion_controller/motion_controller.h"
#include "./controllers/device_controller/device_controller.h"
#include "./controllers/registrator.h"
#include "../common/settings/settings_manager.h"

enum HARDWARE_EVENT {
    DeviceControllerConnected,
    DeviceControllerDisconnected,
    MotionControllerConnected,
    MotionControllerDisconnected,
    SensorStateChanged,
    DeviceStateChanged,
    CurrentPositionChanged,
};

struct HARDWARE_EVENT_DATA {
    HARDWARE_EVENT_DATA(QList<QVariant> params = {}): signalParams(params) {}
    QList<QVariant> signalParams;
};

class HardwareDriverTests;

/**
 * @brief Класс драйвер
 *
 * @warning Реализует паттерн Singleton
 *
 * Единая точка доступа к дереву моделей.
 * Основная задача класса: обеспечение взаимодействия компомнентов системы между собой.
 *
 * Все взаимодействие между компонентами происходит через этот класс.
 *
 * В каждый момент времени позволяет получить текущее состояние любой системы станка.
 *
 * Содержит набор сигналов, подписавшись на которые
 * можно следить за изменениями в определенной компоненте станка в режиме реального времени.
 *
 * Запускает сценарии бизнес-логики, реализованные по средствам интеракторов.
 */
class HardwareDriver : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Предоставляет доступ к объекту класса
     * @return ссылка на объект класса
     */
    static HardwareDriver& getInstance();

    /**
      * @brief Деструктор класса
      */
    ~HardwareDriver();

    bool isConnected() const;

    void registerHandler(HARDWARE_EVENT event, const std::function<void(HARDWARE_EVENT_DATA)> &handler);
    void resetHandlers();

    AxesRepository& getMotionController();
    SensorsRepository& getSensors();

    void moveTo(QMap<Axis::Id, double> absPos);
    void moveOffset(QMap<Axis::Id, double> relPos);
    void stopMoving();
    bool isMoving();

private:
    QList<QMetaObject::Connection> m_systemSlotsInfo;
    QList<QMetaObject::Connection> m_userSlotsInfo;

    /// Сервер для подключения адаптеров
    WebSocketGateway m_adapterServer;
    MotionController m_motionController;
    DeviceController m_deviceController;
    Registrator m_controllerRegistrator;

    /**
     * @brief Создает объект класса
     * @param parent родительский объект
     */
    HardwareDriver(QObject *parent = nullptr);

    /**
     * @brief Запрещаем копи-конструктор
     */
    HardwareDriver(HardwareDriver const&) = delete;

    /**
     * @brief Запрещаем operator =
     */
    HardwareDriver& operator =(HardwareDriver const&) = delete;

    /**
     * @brief Подключет слоты к сигналам полей класса
     */
    void setupSystemSlots();

    /**
     * @brief Отключает слоты от сигналов полей класса
     */
    void resetSystemSlots();

    void testWrapper(QtJson::JsonObject msg);

signals:

public slots:

private slots:
friend class HardwareDriverTests;
};

#endif // HARDWAREDRIVER_H
