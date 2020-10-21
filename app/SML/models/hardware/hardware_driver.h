#ifndef HARDWAREDRIVER_H
#define HARDWAREDRIVER_H

#include <QObject>
#include <QQueue>

#include "./models/services/adapters/launcher/adapters_launcher.h"
#include "./controllers/adapters/adapter_gateway.h"
#include "./controllers/motion_controller/motion_controller.h"
#include "./controllers/device_controller/device_controller.h"
#include "./controllers/registrator.h"
#include "./models/settings_manager/settings_manager.h"

enum HARDWARE_EVENT {
    DeviceControllerConnectionStateChanged,
    MotionControllerConnectionStateChanged,
    SensorStateChanged,
    DeviceStateChanged,
    CurrentPositionChanged,
};

/**
 * @brief Класс драйвер
 *
 * @warning Реализует паттерн Singleton
 *
 * Единая точка доступа к дереву моделей в системе (Router).
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

    QMetaObject::Connection registerHandler(HARDWARE_EVENT event, std::function<void()> const& handler);

private:
    QList<QMetaObject::Connection> m_slotsInfo;

    /// Сервер для подключения адаптеров
    AdapterGateway m_adapterServer;
    MotionController m_motionController;
    DeviceController m_deviceController;
    Registrator m_adapterRegistrator;
    AdaptersLauncher m_adaptersLauncher;

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
    void setupSlots();

    /**
     * @brief Отключает слоты от сигналов полей класса
     */
    void resetSlots();

signals:

public slots:

private slots:
    /**
     * @brief Производит остановку WebSocket сервера для подключения адаптеров
     */
    void stopAdapters();

    void launchAdapters();
};

#endif // HARDWAREDRIVER_H
