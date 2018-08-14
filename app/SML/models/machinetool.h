#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>

#include "models/repository/repository.h"
#include "models/types/server/smlserver.h"

#include "models/services/connections/monitor/connectionsmonitor.h"
#include "models/services/points/monitor/pointsmonitor.h"
#include "models/services/sensors/monitor/sensorsmonitor.h"
#include "models/services/devices/spindels/monitor/spindelsmonitor.h"
#include "models/services/devices/spindels/switch/switchspindel.h"
#include "models/services/gcodes/monitor/gcodesmonitor.h"

// сделать класс синглтоном?

/**
 * @brief Класс станок
 *
 * Корневой класс моделей в системе.
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
    static MachineTool& getInstance();

    /**
      * @brief Деструктор класса Станок
      */
    ~MachineTool();

    /**
     * @brief Предоставляет доступ к репозиторию, где хранится текущее состояние станка
     * @return
     */
    Repository* repository();

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
    int getLastError();

    /**
     * @brief Устанавливает значение последней ошибки
     * @param value код ошибки
     */
    void setLastError(int value);

    MachineTool(MachineTool const&) = delete;
    MachineTool& operator =(MachineTool const&) = delete;

protected:

    /// Репозиторий, хранящий текущее состояние систем станка
    QScopedPointer<Repository> m_repository;

    /// Сервер для подключения адаптеров
    QScopedPointer<SMLServer> m_adapterServer;

    /// Монитор текущих подключений к серверу адаптеров
    QScopedPointer<ConnectionsMonitor> m_connectionMonitor;

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
    /// [-255;0) (0;255] - коды ошибок. Чем больше по модулю от нуля, тем ошибка критичнее.
    int m_lastError;

    /**
     * @brief Подключет слоты к сигналам полей класса
     */
    void setupConnections();

    /**
     * @brief Отключает слоты от сигналов полей класса
     */
    void resetConnections();

private:
    /**
     * @brief Создает объект класса станок
     * @param parent - родительский объект
     */
    MachineTool(QObject *parent = nullptr);
    //MachineTool(MachineTool const&); // Don't Implement
    //void operator=(MachineTool const&); // Don't implement

signals:
    /**
     * @brief Сигнал подключения адаптера U1
     */
    void u1Connected();

    /**
     * @brief Сигнал отключения адаптера U1
     */
    void u1Disconnected();

    /**
     * @brief Сигнал возникновения ошибки в работе станка
     * @param code - код возникшей ошибки
     */
    void errorOccured(int code);

    /**
     * @brief Сигнал изменения состояния датчика
     * @param sensorName уникальный идентификатор датчика
     * @param color цвет текущего состояния датчика (переписать на bool параметр)
     */
    void sensorStateChanged(QString sensorName, QColor color);

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
     * @param content содержимое файла G-кодов в формате строки
     */
    void gcodesFileContentUpdated(QString content);

public slots:
    /// Включает устройство
    void switchSpindelOn(QString index, size_t rotations);
    void switchSpindelOff(QString index);

protected slots:
    /// пишем даные в репозиторий
    void onServer_U1Connected();
    void onServer_U1Disconnected();
    void onServer_ErrorOccured(int errorCode);
    void onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices);

    /// обрабатываем данные от монитора
    void onConnectionMonitor_U1Connected();
    void onConnectionMonitor_U1Disconnected();

    void onPointsMonitor_PointsUpdated();

    void onSensorMonitor_StateChanged(QString sensorName, bool state);
    void onSpindelsMonitor_StateChanged(QString index, bool state, size_t rotations);

    void onGCodesMonitor_FilePathUpdated(QString path);
    void onGCodesMonitor_FileContentUpdated(QString content);
};

#endif // MACHINETOOL_H
