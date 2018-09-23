#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QFile>
#include <QFileDialog>

#include "models/types/structs.h"
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
 * @brief Класс Репозиторий.
 *
 * Предназначен для хранения всей оперативной информации о станке:
 * подключения, список устройств и датчиков и их состояния, состояния осей,
 * текущие координаты и прочее.
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

    // Connections
    // Sensors
    // Devices
    // Points
    // G-Codes

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
     * @warning Бросает исключение InvalidArgumentException, если устройство не найдено.
     * @return ссылка на устройство
     */
    Device& getDevice(size_t index);

    /**
     * @brief Возвращает ссылку на датчик
     * @param name уникальный идетификатор датчика
     * @warning Бросает исключение InvalidArgumentException, если датчик не найден.
     * @return ссылка на датчик
     */
    Sensor& getSensor(QString uid);

    /**
     * @brief Возвращает список имен всех датчиков
     * @return список уникальных имен всех доступных датчиков
     */
    QStringList getAllSensorsNames();

    /**
     * @brief Возвращает текущие настройки датчика по его имени
     * @param name уникальное имя датчика
     * @return список текущих настроек датчика
     */
    QMap<QString, QString> getSensorSettings(QString name);

    /**
     * @brief Устанавливает текущее значение УП в G-Codes
     * @param data УП в G-Codes
     */
    void setGCodes(const QString &data);

    /**
     * @brief Возвращает текущую УП в G-Codes
     * @return УП в G-Codes
     */
    QString getGCodesProgram();

    /**
     * @brief Возвращает текущие координаты станка
     * [0] элемент списка содержит текущие координаты относительно Нуля,
     * [1] элемент списка содержит текущие координаты относительно Базы,
     * [2] элемент списка содержит текущие координаты точки Парк.
     * @return координаты станка
     */
    QList<Point> getMachineToolCoordinates();

    /**
     * @brief Возвращает текущие настройки всех доступных датчиков
     * @return настройки всех доступных датчиков
     */
    QStringList getAllSensorsSettings();

    /**
     * @brief Возвращает список всех доступных устройств
     * @warning Возвращает неуникальные идентификаторы устройств.
     * @return список неуникальных имен устройств
     */
    QStringList getAllDevicesLabels();

    /**
     * @brief Возвращает настройки всех доступных устройств
     * @return настройки для всех доступных устройств
     */
    QList<QStringList> getAllDevicesSettings();

    /**
     * @brief Возвращает список устройств, необходимых для отображения в Наладке
     * @warning Возвращает неуникальные имена устрйоств
     * @return список устройств, необходимых для отображения в наладке
     */
    QStringList getAllOnScreenDevicesLabels();

    /**
     * @brief Возвращает текущее состояние устройств для отображения в Наладке
     * Формат: map <uid устройства, вкл (true) / выкл (false)>
     * @return Список состояний устройств, необходимых для отображения в Наладке
     */
    QMap<QString, bool> getAllOnScreenDevicesStates();

    /**
     * @brief Возвращает названия всех доступных осей координат
     * @return список доступных осей координат
     */
    QStringList getAxisesNames();

    /**
     * @brief Возвращает настройки доступных осей координат
     * @return настройки всех доступных осей координат
     */
    QStringList getAxisesSettings();

    /**
     * @brief Возвращает список доступных опций
     * @return список доступных опций
     */
    QStringList getOptionsLabels();

    /**
     * @brief Добавляет точку
     * @param coordinates координаты точки
     */
    void addPoint(QStringList coordinates);

    /**
     * @brief Возвращает список координат всех доступных точек
     * @return список координат всех доступных точек
     */
    QList<QStringList> getPoints();

    /**
     * @brief Возвращает координаты точки по ее индексу
     * @param index индекс (номер, идентификатор) точки
     * @return координаты точки
     */
    QStringList getPoint(unsigned int index);

    /**
     * @brief Удаляет точку
     * @param index индекс (номер, идентификатор) точки
     */
    void deletePoint(unsigned int index);

    /**
     * @brief Обнновляет координаты точки
     * @param coordinates новые координаты точки
     * @param index индекс (номер, идентификатор) точки
     */
    void updatePoint(QStringList coordinates, unsigned int index);

    /**
     * @brief Возвращает путь до открытого файла
     * @param type тип файла (gcodes / sml. По умолчанию gcodes)
     * @return путь до текущего файла
     */
    QString getFilePath(QString type = "gcodes");

    /**
     * @brief Включает / Отключает контроль габаритов
     * @param enable вкл (true) / выкл (false)
     */
    void setSoftLimitsMode(bool enable);

    /**
     * @brief Возвращает порт, на котором работает сервер
     * @return строковое представления номера порта
     */
    QString getServerPort();

    /**
     * @brief Возвращает размер буфера датчиков
     * @return размер буфера датчиков
     */
    QString getSensorsBufferSize();

    /**
     * @brief Возвращает размер буфера устройств
     * @return размер буфера устройств
     */
    QString getDevicesBufferSize();

    /**
     * @brief Возвращает список доступных шпинделей
     * @return список доступных шпинделей
     */
    QList<Spindel *> getSpindels();

    /**
     * @brief Возвращает ссылку на шпиндель
     * @param uid уникальный идентифиактор шпинделя (уникальный идентификатор устройства)
     * @warning Бросает исключение InvalidArgumentException, если шпиндель не найден.
     * @return ссылка на шпиндель
     */
    Spindel& getSpindel(QString uid);

    /**
     * @brief Устанавливает обновленное значение шпинделя
     * @param uid уникальный идентифиактор шпинделя (уникальный идентификатор устройства)
     * @param enable состояние шпинделя, вкл (true) / выкл (false)
     * @param rotations число оборотов в минуту
     * @warning Бросает исключение InvalidArgumentException, если шпиндель не найден.
     */
    void setSpindelState(QString uid, bool enable, size_t rotations);

    /**
     * @brief Экспортирует настройки станка в *.ini файл
     */
    void exportSettings();

    /**
     * @brief Импортирует настройки станка из *.ini файла
     */
    void importSettings();

    /**
     * @brief Открывает файл с УП в G-Codes
     */
    void openGCodesFile();

    /**
     * @brief Сохраняет УП в G-Codes в тот же файл
     * @param data УП в G-Codes
     */
    void saveGCodesFile(const QString data);

    /**
     * @brief Сохраняет УП в G-Codes в другой файл
     * @param data УП в G-Codes
     */
    void saveGCodesFileAs(const QString data);

    /**
     * @brief Инициализирует новый файл G-Codes
     */
    void newGCodesFile();

    /**
     * @brief Добавляет содержимое файла G-Codes к текущей УП
     * @param data текущая УП в G-Codes
     */
    void addGCodesFile(const QString data);

    /**
     * @brief Возвращает текущее значение верхнего предела скорости перемещения
     * @return максимальная скорость перемещения
     */
    double getVelocity() const;

    /**
     * @brief Устанавливает новое значение верхнего предела скорости перемещения
     * @param velocity максимальная скорость перемещения
     */
    void setVelocity(double velocity);

protected:
    /// Менеджер настроек
    QScopedPointer<SettingsManager> m_settingsManager;

    /// Менеджер точек
    QScopedPointer<PointsManager> m_pointsManager;

    /// Менеджер файлов G-Codes
    QScopedPointer<GCodesFilesManager> m_gcodesFilesManager;

    // Настройки сервера
    /// Номер порта сервера
    size_t m_port;

    /// Величина буфера датчиков
    size_t m_sensorsBufferSize;

    /// Величина буфера устройств
    size_t m_devicesBufferSize;

    // Подключения
    /// Адаптер контроллера U1
    QScopedPointer<Connection> m_u1Connection;

    /// Адаптер контроллера U2
    QScopedPointer<Connection> m_u2Connection;

    // Датчики
    /// Список доступных датчиков
    QList< QSharedPointer<Sensor> > m_sensors;

    /// Буфер датчиков
    QScopedPointer<SensorsBuffer> m_sensorsBuffer;

    // Устройства
    /// Список доступных шпинедлей
    QList< QSharedPointer<Spindel> > m_spindels;

    /// Список доступный дополнительных устройств
    QList< QSharedPointer<SupportDevice> > m_supportDevices;

    // Оси
    /// Список доступных координатных осей
    QList< QSharedPointer<Axis> > m_axises;

    /// Координаты точки Ноль
    Point m_zeroCoordinates;

    /// Координаты точки Парк
    Point m_parkCoordinates;

    /// Максимальная скорость перемещения
    double m_velocity;

    /**
     * @brief Последовательно загружает все настройки станка
     */
    void loadSettigs();

    /**
     * @brief Загружает настройки сервера
     */
    void loadServerSettings();

    /**
     * @brief Загружает настройки датчиков
     */
    void loadSensorsSettings();

    /**
     * @brief Загружает настройки устройств
     */
    void loadDevicesSettings();

    /**
     * @brief Загружает настройки координатных осей
     */
    void loadAxisesSettings();

    /**
     * @brief Возвращает текущие координаты относительно Базы
     * @return текущие координаты станка в абсолютной системе координат
     */
    Point getCurrentCoordinatesFromBase();

    /**
     * @brief Возвращает текущие координаты относительно точки Ноль
     * @return текущие координаты станка в относительной системе координат
     */
    Point getCurrentCoordinatesFromZero();

    /// Класс-друг!
    friend class MachineTool;

signals:

public slots:

protected slots:
};

#endif // REPOSITORY_H
