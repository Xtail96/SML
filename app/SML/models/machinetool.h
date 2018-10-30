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

/**
 * @brief Класс станок
 *
 * @warning Реализует паттерн Singleton
 *
 * Единая точка доступа к дереву моделей в системе.
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
    Repository* getRepository();

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

    /**
     * @brief Запрещаем копи-конструктор
     */
    MachineTool(MachineTool const&) = delete;

    /**
     * @brief Запрещаем operator =
     */
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
     * @param parent родительский объект
     */
    MachineTool(QObject *parent = nullptr);

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
    /**
     * @brief Запускает сценарий включения шпинделя
     * @param index уникальный идентификатор устройства
     * @param rotations частота вращения (обороты в минуту)
     */
    void switchSpindelOn(QString index, size_t rotations);

    /**
     * @brief Запускает сценарий выключения шпинделя
     * @param index уникальный идентификатор устройства
     */
    void switchSpindelOff(QString index);

protected slots:
    /**
     * @brief Обрабатывает сигнал от сервера адаптеров о подключении адаптера U1
     * (запись данных в репозитоий)
     */
    void onServer_U1Connected();

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров об отключении адаптера U1
     * (запись данных в репозиторий)
     */
    void onServer_U1Disconnected();

    /**
     * @brief Обрабатывает сигнал от сервера адаптеров об изменении состояния адаптера U1
     * (запись данных в репозиторий)
     * @param sensors обновленное состояние датчиков
     * @param devices обновленное состояние устройств
     */
    void onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices);

    /**
     * @brief Обрабатывает сигнал об ошибке станка
     * 1) Устанавливает значение переменной, хранящей код ошибки.
     * 2) Вызывает сценарий обработки ошибки.
     * 3) Испускает сигнал о возникновении ошибки.
     * @param errorCode код ошибки
     */
    void onServer_ErrorOccured(int errorCode);

    /**
     * @brief Обрабатывает сигнал от монитора подключений об изменнии сотояния подключения адаптера U1
     * @param connected обновленное состояние подключения. True - адаптер подключен. False - адаптер отключен
     */
    void onConnectionMonitor_U1StateChanged(bool connected);

    /**
     * @brief Обрабатывает сигнал от монитора точек об изменении состояния точек
     * (испускает сигнал о том, что состояние точек изменилось)
     */
    void onPointsMonitor_PointsUpdated();

    /**
     * @brief Обрабатывает сигнал от монитора датчиков об изменении состояния датчика
     * (испускает сигнал о том, что состояние датчика изменилось)
     *
     * @param sensorName уникальный идентификатор датчика
     * @param state обновленное состояние датчика, true = on / false = off
     */
    void onSensorMonitor_StateChanged(QString sensorName, bool state);

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
     * @param content содержимое файла в формате строки
     */
    void onGCodesMonitor_FileContentUpdated(QString content);
};

#endif // MACHINETOOL_H
