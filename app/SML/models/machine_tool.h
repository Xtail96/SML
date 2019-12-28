#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>
#include <QQueue>

#include "models/repository/repository.h"
#include "models/machine_tool_elements/adapter/server/sml_adapter_server.h"

#include "models/services/adapters/monitor/adapters_monitor.h"
#include "models/services/points/monitor/points_monitor.h"
#include "models/services/sensors/monitor/sensors_monitor.h"
#include "models/services/devices/spindels/monitor/spindels_monitor.h"
#include "models/services/devices/spindels/switch/switch_spindel_interactor.h"
#include "models/services/gcodes/monitor/gcodes_monitor.h"
#include "models/services/program/prepare_execution_queue_interactor.h"
#include "models/services/axises/monitor/axises_monitor.h"
#include "models/services/errors/error_flags_monitor.h"

#include "models/services/adapters/launcher/adapters_launcher.h"

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
     * @brief Производит запуск WebSocket сервера для подключения адаптеров
     */
    void startAdapterServer();

    /**
     * @brief Производит остановку WebSocket сервера для подключения адаптеров
     */
    void stopAdapterServer();

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

    /**
     * @brief Устанавливает значение ошибки
     * @param code код ошибки
     */
    void setErrorFlag(ERROR_CODE code);

    void removeErrorFlag(ERROR_CODE code);

    bool getBased() const;
    void setBased(bool based);

    void launchAdapters();
    void stopAdapters();

private:

    /// Репозиторий, хранящий текущее состояние систем станка
    QScopedPointer<Repository> m_repository;

    /// Сервер для подключения адаптеров
    QScopedPointer<SMLAdapterServer> m_adapterServer;

    /// Ошибки возникшие при работе системы
    /// Данную переменную необходимо проверять, при отправке данных на станок.
    QScopedPointer<SmlErrorFlags> m_errors;

    /// Монитор ошибок
    QScopedPointer<ErrorFlagsMonitor> m_errorFlagsMonitor;

    /// Монитор текущих подключений к серверу адаптеров
    QScopedPointer<AdaptersMonitor> m_adaptersMonitor;

    /// Монитор текущего состояния точек
    QScopedPointer<PointsMonitor> m_pointsMonitor;

    /// Монитор текущего состояния датчиков
    QScopedPointer<SensorsMonitor> m_sensorsMonitor;

    /// Монитор текущего состояния шпинделей
    QScopedPointer<SpindelsMonitor> m_spindelsMonitor;

    /// Монитор текущего состояния G-кодов
    QScopedPointer<GCodesMonitor> m_gcodesMonitor;

    /// Монитор осей координат
    QScopedPointer<AxisesMonitor> m_axisesMonitor;

    /// Очередь сообщений, ожидающих отправки.
    QQueue<QByteArray> m_executionQueue;

    /// Проводилась ли базировка станка (можно ли доверять координатам осей)
    bool m_based;

    QScopedPointer<AdaptersLauncher> m_adaptersLauncher;

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

    void nextCommandSent(QByteArray package);

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

    void startProgramProcessing();
    bool prepareExecutionQueue(QStringList gcodes, bool resolveToCurrentPositionIsNeed = false);
    void pauseExecutionQueueProcessing();
    void resumeExecutionQueueProcessing();
    void stopExecutionQueueProcessing();

    void moveToPoint(Point pointFromBase);

    void moveToSensor(QString sensorUid);
    void moveToBase();

    void resetCurrentCoordinates();

private slots:
    void onRepository_ErrorOccurred(ERROR_CODE flag);

    void onErrorFlagsMonitor_ErrorFlagsStateChanged();

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров о подключении адаптера U1
     * (запись данных в репозитоий)
     */
    void onAdapterServer_U1Connected();

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров об отключении адаптера U1
     * (запись данных в репозиторий)
     */
    void onAdapterServer_U1Disconnected();

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров об изменении состояния адаптера U1
     * (запись данных в репозиторий)
     * @param sensors обновленное состояние датчиков
     * @param devices обновленное состояние устройств
     * @param workflowState состояние выполнения работ
     * @param lastError код ошибки
     */
    void onAdapterServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, unsigned int workflowState, ERROR_CODE lastError);

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров о подключении адаптера U2
     * (запись данных в репозитоий)
     */
    void onAdapterServer_U2Connected();

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров об отключении адаптера U2
     * (запись данных в репозиторий)
     */
    void onAdapterServer_U2Disconnected();

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров об изменении состояния адаптера U2
     * (запись данных в репозиторий)
     * @param coordinates текущие координаты по осям
     * @param workflowState состояние выполнения работ
     * @param lastError код ошибки
     */
    void onAdapterServer_U2StateChanged(QMap<QString, double> coordinates, unsigned int workflowState, ERROR_CODE lastError);

    /**
     * @brief Обрабатывает сигнал об ошибке станка
     * 1) Устанавливает значение переменной, хранящей код ошибки.
     * 2) Вызывает сценарий обработки ошибки.
     * 3) Испускает сигнал о возникновении ошибки.
     * @param errorCode код ошибки
     */
    void onAdapterServer_ErrorOccurred(ERROR_CODE errorCode);

    /**
     * @brief Обрабатывает сигнал от монитора адаптеров об изменнии сотояния подключения адаптеров
     */
    void onAdaptersMonitor_AdapterConnectionStateChanged();

    /**
     * @brief Обрабатывает сигнал от монитора адаптеров об изменнии сотояния выполнения заданий адаптеров
     */
    void onAdaptersMonitor_AdapterWorkflowStateChanged();

    /**
     * @brief Обрабатывает сигнал от монитора точек об изменении состояния точек
     * (испускает сигнал о том, что состояние точек изменилось)
     */
    void onPointsMonitor_PointsUpdated();

    /**
     * @brief Обрабатывает сигнал от монитора датчиков об изменении состояния датчика
     * (испускает сигнал о том, что состояние датчика изменилось)
     *
     * @param sensorUid уникальный идентификатор датчика
     * @param state обновленное состояние датчика, true = on / false = off
     */
    void onSensorMonitor_StateChanged(QString sensorUid, bool state);

    /**
     * @brief Обрабатывает сигнал от монитора шпинделей об изменении состояния шпинделя
     * (испускает сигнал о том, что состояние шпинделя изменилось)
     *
     * @param index уникальный идентификатор устройства
     * @param state обновленное состояние шпинделя, true = on / false = off
     * @param rotations частота вращения шпинделя (обороты в минуту)
     */
    void onSpindelsMonitor_StateChanged(QString index, bool state, size_t rotations);

    /**
     * @brief Обрабатывает сигнал от монитора G-кодов об изменении пути к текущему файлу
     * (испускает сигнал о том, что обновился путь к текущему файлу)
     *
     * @param path обновленный путь к файлу (включая имя файла)
     */
    void onGCodesMonitor_FilePathUpdated(QString path);

    /**
     * @brief Обрабатывает сигнал от монитора G-кодов об изменении содержимого файла
     * (испускает сигнал о том, что обновилось содержимое файла)
     *
     * @param content содержимое файла в формате списка строк
     */
    void onGCodesMonitor_FileContentUpdated(QStringList content);

    /**
     * @brief Обрабатывает сигнал от монитора Осей об изменении текущей позиции оси
     * (испускает сигнал о том, что изменились текущие координаты по оси)
     *
     * @param uid идентификатор оси (unused)
     * @param position позиция по оси (unused)
     */
    void onAxisesMonitor_AxisCurrentPositionChanged(QString, double);

    /**
     * @brief Отправляет следующую команду в очереди на исполнение
     */
    void sendNextCommand();

    /**
     * @brief Обрабатывает изменение workflow статуса адаптеров
     * @param u1State состояние выполнения работ на контроллере U1
     * @param u2State состояние выполнения работ на контроллере U2
     */
    void onMachineTool_WorkflowStateChanged(unsigned int u1WorkflowState, unsigned int u2WorkflowState);
};

#endif // MACHINETOOL_H
