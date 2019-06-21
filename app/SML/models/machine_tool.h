#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>
#include <QQueue>

#include "models/repository/repository.h"
#include "models/server/sml_server.h"

#include "models/services/adapters/monitor/adapters_monitor.h"
#include "models/services/points/monitor/points_monitor.h"
#include "models/services/sensors/monitor/sensors_monitor.h"
#include "models/services/devices/spindels/monitor/spindels_monitor.h"
#include "models/services/devices/spindels/switch/switch_spindel_interactor.h"
#include "models/services/gcodes/monitor/gcodes_monitor.h"
#include "models/services/program/prepare_execution_queue_interactor.h"

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
     * @brief Возвращает код последней ошибки
     * @return код ошибки
     */
    ERROR_CODE getLastError();

    /**
     * @brief Устанавливает значение последней ошибки
     * @param value код ошибки
     */
    void setLastError(ERROR_CODE value);

private:

    /// Репозиторий, хранящий текущее состояние систем станка
    QScopedPointer<Repository> m_repository;

    /// Сервер для подключения адаптеров
    QScopedPointer<SMLServer> m_adapterServer;

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

    /// Код последней возникшей ошибки
    /// Данную переменную необходимо проверять, при отправке данных на станок.
    /// 0 - ошибок нет.
    /// (0;255] - коды ошибок. Описаны в соотвествующем файле.
    ERROR_CODE m_lastError;

    /// Очередь сообщений, ожидающих отправки.
    QQueue<QByteArray> m_executionQueue;

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

    ERROR_CODE checkMachineToolState();

    bool checkAdapterConnections();

signals:
    /**
     * @brief Сигнал изменения состояния ошибки в работе станка
     * @param code - код ошибки
     */
    void errorStateChanged(ERROR_CODE code);

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

    void workflowStateChanged(bool u1Free, bool u2Free);

    void programCompletedSuccesfully();

    void positionChanged();

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

    void executeProgram();

private slots:
    void onRepository_ErrorOccurred(ERROR_CODE code);

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
     * @param workflowState состояние выполнения работ
     * @param lastError код ошибки
     */
    void onAdapterServer_U2StateChanged(unsigned int workflowState, ERROR_CODE lastError);


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
     * @brief Отправляет следующую команду в очереди на исполнение
     */
    void sendNextCommand();

    /**
     * @brief Обрабатывает изменение workflow статуса адаптеров
     * @param u1Free контроллер U1 свободен (true/false)
     * @param u2Free контроллер U2 свободен (true/false)
     */
    void onMachineTool_WorkflowStateChanged(bool u1Free, bool u2Free);
};

#endif // MACHINETOOL_H
