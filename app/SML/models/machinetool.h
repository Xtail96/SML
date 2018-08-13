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


/*!
 * \brief Класс Станок
 * Является классом модели верхнего уровня: презентеры ведут взаимодействие с этим классом.
 * Управляет всеми менеджерами, подготавивает данные для вывода в интерфейс.
 */
class MachineTool : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса Станок
     * \param parent - указатель на объект (по умолчанию равен nullptr)
     */
    explicit MachineTool(QObject *parent = nullptr);

    /*!
      * \brief Деструктор класса Станок
      */
    ~MachineTool();

    Repository* repository();

    /// Производит запуск сервера
    void startServer();

    /// Производит остановку сервера
    void stopServer();

    QStringList getCurrentConnections();
    QString getServerPort();

    void setLastError(int value);

protected:
    QScopedPointer<Repository> m_repository;
    QScopedPointer<SMLServer> m_server;

    QScopedPointer<ConnectionsMonitor> m_connectionMonitor;
    QScopedPointer<PointsMonitor> m_pointsMonitor;
    QScopedPointer<SensorsMonitor> m_sensorsMonitor;
    QScopedPointer<SpindelsMonitor> m_spindelsMonitor;
    QScopedPointer<GCodesMonitor> m_gcodesMonitor;

    int m_lastError;

    /// Подключает нужные слоты к полям и сигналам класса
    void setupConnections();

    /// Отключает слоты от полей и сигналов класса
    void resetConnections();

signals:
    void u1Connected();
    void u1Disconnected();
    void errorOccured(int code);
    void sensorStateChanged(QString sensorName, QColor color);
    void spindelStateChanged(QString index, bool enable, size_t currentRotations);
    void pointsUpdated();
    void gcodesFilePathUpdated(QString path);
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
