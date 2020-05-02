#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>
#include <QQueue>

#include "models/repository/repository.h"
#include "models/machine_tool_elements/adapter/server/sml_adapter_server.h"

#include "models/services/devices/spindels/switch/switch_spindel_interactor.h"
#include "models/services/gcodes/prepare_execution_queue/prepare_execution_queue_interactor.h"
#include "models/services/errors/error_flags_monitor.h"

#include "models/services/adapters/launcher/adapters_launcher.h"
#include "models/services/adapters/get_current_state/get_adapter_current_state_interactor.h"

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

    static bool isProgramEmpty(QStringList gcodes);

private:

    /// Репозиторий, хранящий текущее состояние систем станка
    Repository m_repository;

    /// Сервер для подключения адаптеров
    SMLAdapterServer m_adapterServer;

    /// Ошибки возникшие при работе системы
    /// Данную переменную необходимо проверять, при отправке данных на станок.
    SmlErrorFlags m_errors;

    /// Монитор ошибок
    ErrorFlagsMonitor m_errorFlagsMonitor;

    /// Очередь сообщений, ожидающих отправки.
    QQueue<QByteArray> m_executionQueue;

    /// Проводилась ли базировка станка (можно ли доверять координатам осей)
    bool m_based;

    AdaptersLauncher m_adaptersLauncher;

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

    bool isGCodesCorrect(QStringList gcodes);
    void startProgramProcessing();
    bool prepareExecutionQueue(QStringList gcodes, bool resolveToCurrentPosition = false);
    void pauseExecutionQueueProcessing();
    void resumeExecutionQueueProcessing();
    void stopExecutionQueueProcessing();

    void stepMove(QMap<QString, double> steps);
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
    void onAdapter_ConnectionStateChanged();

    /**
     * @brief Обрабатывает сигнал от монитора адаптеров об изменнии сотояния выполнения заданий адаптеров
     */
    void onAdapter_WorkflowStateChanged();

    /**
     * @brief Обрабатывает сигнал от монитора точек об изменении состояния точек
     * (испускает сигнал о том, что состояние точек изменилось)
     */
    void onRepository_PointsUpdated();

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
