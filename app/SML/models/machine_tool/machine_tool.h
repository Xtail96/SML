#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>
#include <QQueue>

#include "models/repository/repository.h"

#include "models/services/devices/spindels/switch/switch_spindel_interactor.h"
#include "models/services/gcodes/prepare_execution_queue/prepare_execution_queue_interactor.h"
#include "models/errors/sml_error_flags.h"

#include "models/services/adapters/launcher/adapters_launcher.h"
#include "models/services/adapters/get_current_state/get_adapter_current_state_interactor.h"

#include "./controllers/adapters/adapter_gateway.h"
#include "./controllers/motion_controller/motion_controller.h"
#include "./controllers/device_controller/device_controller.h"
#include "./controllers/registrator.h"

/**
 * @brief Класс станок
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
class MachineTool : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Предоставляет доступ к объекту класса
     * @return ссылка на объект класса
     */
    static MachineTool& getInstance();

    /**
      * @brief Деструктор класса Станок
      */
    ~MachineTool();

    /**
     * @brief Предоставляет доступ к репозиторию, где хранится текущее состояние станка
     * @return
     */
    Repository& getRepository();

    /**
     * @brief Возвращает список подключенных адаптеров
     * @return Список подключенных авдптеов в формате списка строк
     */
    QStringList getConnectedAdapters();

    /**
     * @brief Возвращает номер порта, на котором запущен WebSocket сервер для подключения
     * адаптеров
     * @return номер порта, на котором запущен WebSocket сервер для подключения
     * адаптеров
     */
    QString getAdapterServerPort();

    /**
     * @brief Возвращает код ошибок
     * @return код ошибок
     */
    QList<ERROR_CODE> getCurrentErrorFlags();

    bool getBased() const;

private:
    QList<QMetaObject::Connection> m_connections;

    /// Репозиторий, хранящий текущее состояние систем станка
    Repository m_repository;

    /// Сервер для подключения адаптеров
    AdapterGateway m_adapterServer;
    MotionController m_motionController;
    DeviceController m_deviceController;
    Registrator m_adapterRegistrator;
    AdaptersLauncher m_adaptersLauncher;

    /// Ошибки возникшие при работе системы
    /// Данную переменную необходимо проверять, при отправке данных на станок.
    SmlErrorFlags m_errors;

    /// Очередь сообщений, ожидающих отправки.
    QQueue<QByteArray> m_executionQueue;
    QMetaObject::Connection m_sendNextCommandMetaInfo;

    /// Проводилась ли базировка станка (можно ли доверять координатам осей)
    bool m_based;

    /**
     * @brief Создает объект класса станок
     * @param parent родительский объект
     */
    MachineTool(QObject *parent = nullptr);

    /**
     * @brief Запрещаем копи-конструктор
     */
    MachineTool(MachineTool const&) = delete;

    /**
     * @brief Запрещаем operator =
     */
    MachineTool& operator =(MachineTool const&) = delete;

    /**
     * @brief Подключет слоты к сигналам полей класса
     */
    void setupConnections();

    /**
     * @brief Отключает слоты от сигналов полей класса
     */
    void resetConnections();

    void handleErrors();

signals:
    /**
     * @brief Сигнал изменения состояния ошибки в работе станка
     */
    void errorStateChanged(QList<ERROR_CODE> errors);

    /**
     * @brief Сигнал изменения состояния датчика
     * @param sensorName уникальный идентификатор датчика
     * @param state состояние сенсора
     * @param color цвет текущего состояния датчика
     */
    void sensorStateChanged(QString sensorName, bool state);

    /**
     * @brief Сигнал изменения состояния шпинделя
     * @param index уникальный индекс устройства
     * @param enable состояния вкл (true) / выкл (false)
     * @param currentRotations текущее значение оборотов
     */
    void spindelStateChanged(QString index, bool enable, size_t currentRotations);

    /**
     * @brief Сигнал обновления состояния точек
     */
    void pointsUpdated();

    /**
     * @brief Сигнал обновления пути до файла G-кодов
     * @param path обновленный путь к файлу (включая имя файла)
     */
    void gcodesFilePathUpdated(QString path);

    /**
     * @brief Сигнал обновления содержимого фала G-кодов
     * @param content содержимое файла G-кодов в формате списка строк
     */
    void gcodesFileContentUpdated(QStringList content);

    void workflowStateChanged(unsigned int u1WorkflowState, unsigned int u2WorkflowState);

    void commandSent(QByteArray package);

    void taskCompletedSuccesfully();

    void taskCompletedWithErrors();

    void currentCoordinatesChanged();

    void basingStateChanged(bool m_state);

public slots:
    /**
     * @brief Запускает сценарий включения шпинделя
     * @param uid уникальный идентификатор устройства
     * @param rotations частота вращения (обороты в минуту)
     */
    void switchSpindelOn(QString uid, size_t rotations);

    /**
     * @brief Запускает сценарий выключения шпинделя
     * @param uid уникальный идентификатор устройства
     */
    void switchSpindelOff(QString uid);

    bool isProgramEmpty();
    bool isGCodesCorrect();
    void startProgramProcessing();
    void pauseProgramProcessing();
    void resumeProgramProcessing();
    void stopProgramProcessing();

    void stepMove(QMap<QString, double> steps);
    void moveToPoint(Point pointFromBase);

    void moveToSensor(QString sensorUid);
    void moveToBase();

private slots:
    /**
     * @brief Устанавливает значение ошибки
     * @param code код ошибки
     */
    void setErrorFlag(ERROR_CODE code);

    void removeErrorFlag(ERROR_CODE code);

    bool prepareExecutionQueue(QStringList gcodes, bool resolveToCurrentPosition = false);

    /**
     * @brief Отправляет следующую команду в очереди на исполнение
     */
    void sendNextCommand();

    void resetCurrentCoordinates();

    void setBased(bool based);

    /**
     * @brief Производит запуск WebSocket сервера для подключения адаптеров
     */
    void startAdapterServer();

    /**
     * @brief Производит остановку WebSocket сервера для подключения адаптеров
     */
    void stopAdapterServer();

    void launchAdapters();
    void stopAdapters();
};

#endif // MACHINETOOL_H
