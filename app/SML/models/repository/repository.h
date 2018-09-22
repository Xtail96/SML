#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QFile>
#include <QFileDialog>

#include "models/types/axis/axis.h"
#include "models/types/device/spindel.h"
#include "models/types/device/supportdevice.h"
#include "models/types/sensor/sensor.h"
#include "models/types/sensor/sensorsbuffer.h"
#include "models/types/settingsmanager/settingsmanager.h"
#include "models/types/point/pointsmanager.h"
#include "models/types/connection/connection.h"
#include "models/types/gcodes/gcodesfilesmanager/gcodesfilesmanager.h"

class MachineTool;

/**
 * @brief Класс Репозиторий
 *
 * Предназначен для хранения всей оперативной информации о станке:
 * подключения, список устройств и датчиков и их состояния, состояния осей,
 * текущие координаты и прочее
 */
class Repository : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса
     * @param parent родительский объект
     */
    explicit Repository(QObject *parent = nullptr);

    /**
     * @brief Устанавливает состояния подключения адаптера U1
     * @param connected состояние подключения адаптера. подключен (true) / отключен (false)
     */
    void setU1ConnectState(bool connected);

    /**
     * @brief Устанавливает значение состояния датчиков
     * @param sensors обновленное состояние датчиков
     */
    void setU1Sensors(QList<QVariant> sensors);

    /**
     * @brief Устанавливает значение состояния устройств
     * @param devices обновленное состояние устройств
     */
    void setU1Devices(QList<QVariant> devices);

    /**
     * @brief Возвращает ссылку на устройство
     * @param index уникальный индекс устройства
     * @return ссылка на устройство
     */
    Device& getDevice(size_t index);

    /**
     * @brief Возвращает ссылку на датчик
     * @param name уникальное имя датчика
     * @return ссылка на датчик
     */
    Sensor& getSensor(QString name);


    QStringList getSensorNames();
    QMap<QString, QString> getSensorSettings(QString name);

    /// Устанавливает текущее значение G-Codes
    void setGCodes(const QString &data);
    /// Возвращает текущее значение G-Codes
    QString getGCodesProgram();

    /// Возвращает текущие координаты станка
    QList<Point> getMachineToolCoordinates();

    /// Вовращает значения настроей подключенных датчиков
    QStringList getSensorsSettings();

    /// Возвращает список всех подключенных устройств
    QStringList getAllDevicesNames();

    /// Возвращает настройки подключенных устройств
    QList<QStringList> getAllDevicesSettings();

    /// Возвращает список устройств, необходимых для отображения в Наладке
    QStringList getOnScreenDevicesNames();

    /// Возвращает список состояний подулюченных устройств
    /// true = устройство включено, false = устройство выключено
    QList<bool> getOnScreenDevicesStates();

    /// Возвращает названия активных осей координат
    QStringList getAxisesNames();

    /// Возвращает настройки активных осей координат
    QStringList getAxisesSettings();

    /// Возвращает нащвания подключенных опций
    QStringList getOptionsNames();

    void addPoint(QStringList coordinates);

    /// Возвращает список точек
    QList<QStringList> getPoints();

    /// Возвращает координаты точки по ее индексу
    QStringList getPoint(unsigned int number);

    void deletePoint(unsigned int number);

    void updatePoint(QStringList coordinates, unsigned int number);

    /// Возвращает путь до открытого файла
    QString getFilePath(QString type = "gcodes");

    /// Включает или отключает контроль габаритов
    void setSoftLimitsMode(bool enable);

    /// Возвращает список текущих подключений
    QStringList getCurrentConnections();

    /// Возвращает порт, на котором сервер принимает подключения
    QString getServerPort();

    /// Возвращает размер буфера датчиков
    QString getSensorsBufferSize();

    /// Возвращает размер буфера устройств
    QString getDevicesBufferSize();

    QList<Spindel *> getSpindels();

    Spindel* getSpindel(QString index);

    void setSpindelState(QString index, bool enable, size_t rotations);

    /// Производит экспорт настроек станка в *.ini файл
    void exportSettings();

    /// Производит импорт настроек станка из *.ini файла
    void importSettings();

    /// Производит открытие файла G-Codes
    void openGCodesFile();

    /// Производит сохранение G-Codes в том же файле
    void saveGCodesFile(const QString data);

    /// Производит сохранение G-Codes в другом файла
    void saveGCodesFileAs(const QString data);

    /// Производит инициализацию файла G-Codes
    void newGCodesFile();

    /// Производит добавление содержимого файлв G-Codes к существующей УП
    void addGCodesFile(const QString data);

    double getVelocity() const;
    void setVelocity(double velocity);

protected:
    /// Менеджер настроек
    QScopedPointer<SettingsManager> m_settingsManager;

    /// Точки
    QScopedPointer<PointsManager> m_pointsManager;

    /// G-Codes
    QScopedPointer<GCodesFilesManager> m_gcodesFilesManager;

    /// Настройки сервера
    size_t m_port;
    size_t m_sensorsBufferSize;
    size_t m_devicesBufferSize;

    /// Подключения
    QScopedPointer<Connection> m_u1Connection;
    QScopedPointer<Connection> m_u2Connection;

    /// Датчики
    QList< QSharedPointer<Sensor> > m_sensors;
    QScopedPointer<SensorsBuffer> m_sensorsBuffer;

    /// Устройства
    QList< QSharedPointer<Spindel> > m_spindels;
    QList< QSharedPointer<SupportDevice> > m_supportDevices;

    /// Оси
    QList< QSharedPointer<Axis> > m_axises;
    Point m_zeroCoordinates;
    Point m_parkCoordinates;

    double m_velocity;

    void loadSettigs();
    void loadServerSettings();
    void loadSensorsSettings();
    void loadDevicesSettings();
    void loadAxisesSettings();

    Point getCurrentCoordinatesFromBase();
    Point getCurrentCoordinatesFromZero();

    friend class MachineTool;

signals:

public slots:

protected slots:
};

#endif // REPOSITORY_H
