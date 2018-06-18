#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "models/types/axis/axis.h"
#include "models/types/device/spindel.h"
#include "models/types/device/supportdevice.h"
#include "models/types/sensor/sensor.h"
#include "models/types/sensor/sensorsbuffer.h"
#include "models/types/settingsmanager/settingsmanager.h"
#include "models/types/point/point.h"
#include "models/types/connection/connection.h"

class MachineTool;
class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

    void setU1Connected(bool connected);
    void setU1Sensors(QList<QVariant> sensors);
    void setU1Devices(QList<QVariant> devices);
    void setU1Error(int code);

    Device& findDevice(size_t index);

protected:
    /// Менеджер настроек
    QScopedPointer<SettingsManager> m_settingsManager;

    /// Сервер
    size_t m_port;

    /// Подключения
    QScopedPointer<Connection> m_u1Connection;
    QScopedPointer<Connection> m_u2Connection;

    /// Датчики
    QList< QSharedPointer<Sensor> > m_sensors;
    SensorsBuffer m_sensorsBuffer;

    /// Устройства
    QList< QSharedPointer<Spindel> > m_spindels;
    QList< QSharedPointer<SupportDevice> > m_supportDevices;

    /// Оси
    QList< QSharedPointer<Axis> > m_axises;
    Point m_zeroCoordinates;
    Point m_parkCoordinates;

    void loadSettigs();
    void loadServerSettings();
    void loadSensorsSettings();
    void loadDevicesSettings();
    void loadAxisesSettings();

    friend class MachineTool;

signals:

public slots:
};

#endif // REPOSITORY_H
