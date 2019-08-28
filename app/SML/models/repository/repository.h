#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QFile>
#include <QFileDialog>

#include "models/types/structs.h"
#include "models/types/axis/axis.h"
#include "models/types/device/spindel.h"
#include "models/types/device/support_device.h"
#include "models/types/sensor/sensor.h"
#include "models/types/sensor/sensors_buffer.h"
#include "models/settings_manager/settings_manager.h"
#include "models/types/point/points_manager.h"
#include "models/types/adapter/adapter.h"
#include "models/types/gcodes/gcodes_file_manager/gcodes_file_manager.h"

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

    // Settings

    /**
     * @brief Экспортирует настройки станка в *.ini файл
     */
    void exportSettings();

    /**
     * @brief Импортирует настройки станка из *.ini файла
     */
    void importSettings();

    // Adapters

    /**
     * @brief Устанавливает состояние подключения адаптера U1
     * @param connected обновленное состояние подключения адаптера. подключен (true) / отключен (false)
     */
    void setU1ConnectState(bool connected);

    /**
     * @brief Устанавливает новое состоние выполенния работ адаптера U1
     * @param state обновленное состояние выполенения работ адаптера U1 (0 - заданий нет, 1 - контроллер занят, >= 2 - ошибка)
     */
    void setU1WorkflowState(unsigned int state);

    /**
     * @brief Устанавливает состояние подключения адаптера U2
     * @param connected обновленное состояние подключения адаптера. подключен (true) / отключен (false)
     */
    void setU2ConnectState(bool connected);

    /**
     * @brief Устанавливает новое состоние выполенния работ адаптера U2
     * @param state обновленное состояние выполенения работ адаптера U1 (0 - заданий нет, 1 - контроллер занят, >= 2 - ошибка)
     */
    void setU2WorkflowState(unsigned int state);

    /**
     * @brief Возвращает порт, на котором работает сервер
     * @return строковое представления номера порта
     */
    QString getServerPort();

    // Sensors

    /**
     * @brief Устанавливает значение состояния датчиков
     * @param sensors обновленное состояние датчиков
     */
    void setU1Sensors(QList<QVariant> sensors);

    /**
     * @brief Возвращает список уникальных имен всех доступных датчиков
     * @return список уникальных имен всех доступных датчиков
     */
    QStringList getAllSensorsUids();

    /**
     * @brief Возвращает текущие настройки датчика по его имени
     * @param name уникальное имя датчика
     * @return список текущих настроек датчика
     */
    QMap<QString, QString> getSensorSettings(QString uid);

    /**
     * @brief Возвращает текущие настройки всех доступных датчиков
     * @return настройки всех доступных датчиков
     */
    QStringList getAllSensorsSettings();

    /**
     * @brief Возвращает размер буфера датчиков
     * @return размер буфера датчиков
     */
    QString getSensorsBufferSize();

    // Devices

    /**
     * @brief Устанавливает значение состояния устройств
     * @param devices обновленное состояние устройств
     */
    void setU1Devices(QList<QVariant> devices);

    /**
     * @brief Возвращает список всех доступных устройств
     * @warning Возвращает неуникальные идентификаторы устройств.
     * @return список неуникальных имен устройств
     */
    QStringList getAllDevicesLabels();

    /**
     * @brief Возвращает настройки всех доступных шпинделей
     * @return настройки для всех доступных шпинделей
     */
    QStringList getAllSpindelsSettings();

    /**
     * @brief Возвращает настройки всех доступных сопутствующих устройств
     * @return настройки для всех доступных сопутствующих устройств
     */
    QStringList getAllSupportDeviceSettings();

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
     * @brief Устанавливает обновленное значение шпинделя
     * @param uid уникальный идентифиактор шпинделя (уникальный идентификатор устройства)
     * @param enable состояние шпинделя, вкл (true) / выкл (false)
     * @param rotations число оборотов в минуту
     * @warning Бросает исключение InvalidArgumentException, если шпиндель не найден.
     */
    void setSpindelState(QString uid, bool enable, size_t rotations);

    // Points

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

    // Program

    /**
     * @brief Устанавливает текущее значение УП в G-Codes
     * @param data УП в G-Codes
     */
    void setGCodes(const QString &data);

    /**
     * @brief Возвращает текущую УП в G-Codes
     * @return УП в G-Codes
     */
    QStringList getGCodesProgram();

    /**
     * @brief Возвращает путь до открытого файла
     * @param type тип файла (gcodes / sml. По умолчанию gcodes)
     * @return путь до текущего файла
     */
    QString getFilePath(QString type = "gcodes");

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

    // Axises

    /**
     * @brief Возвращает текущие координаты станка
     * [0] элемент списка содержит текущие координаты относительно Нуля,
     * [1] элемент списка содержит текущие координаты относительно Базы,
     * [2] элемент списка содержит текущие координаты точки Парк.
     * @return координаты станка
     */
    QList<Point> getCurrentCoordinates();

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

    void setCurrentCoordinates(Point absCoordinates);

    void setCurrentCoordinates(QMap<QString, double> absCoordinates);

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
     * @brief Включает / Отключает контроль габаритов
     * @param enable вкл (true) / выкл (false)
     */
    void setSoftLimitsMode(bool enable);

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

    // Options

    /**
     * @brief Возвращает список доступных опций
     * @return список доступных опций
     */
    QStringList getOptionsLabels();

    double getMovementStep() const;
    void setMovementStep(double movementStep);

    Point getZeroCoordinates() const;
    void setZeroCoordinates(const Point &zeroCoordinates);

    Point getParkCoordinates() const;
    void setParkCoordinates(const Point &parkCoordinates);

private:
    /// Менеджер настроек
    QScopedPointer<SettingsManager> m_settingsManager;

    /// Менеджер точек
    QScopedPointer<PointsManager> m_pointsManager;

    /// Менеджер файлов G-Codes
    QScopedPointer<GCodesFileManager> m_gcodesFilesManager;

    // Настройки сервера
    /// Номер порта сервера
    qint16 m_port;

    /// Величина буфера датчиков
    size_t m_sensorsBufferSize;

    /// Величина буфера устройств
    size_t m_devicesBufferSize;

    // Подключения
    /// Адаптер контроллера U1
    QScopedPointer<Adapter> m_u1Adapter;

    /// Адаптер контроллера U2
    QScopedPointer<Adapter> m_u2Adapter;

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

    /// Дискретность перемещений из наладки
    double m_movementStep;

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
     * @brief Проверяет наличие датчика в репозитории
     * @param uid уникальный идентификатор датчика
     * @return существует ли датчик с указанным идентификатором
     */
    bool sensorExists(QString uid);

    /**
     * @brief Возвращает ссылку на датчик
     * @param uid уникальный идетификатор датчика
     * @warning Бросает исключение InvalidArgumentException, если датчик не найден.
     * @return ссылка на датчик
     */
    Sensor& getSensor(QString uid);

    /**
     * @brief Возвращает ссылку на устройство
     * @param index уникальный индекс устройства
     * @warning Бросает исключение InvalidArgumentException, если устройство не найдено.
     * @return ссылка на устройство
     */
    Device& getDevice(size_t index);

    /**
     * @brief Возвращает ссылку на шпиндель
     * @param uid уникальный идентифиактор шпинделя (уникальный идентификатор устройства)
     * @warning Бросает исключение InvalidArgumentException, если шпиндель не найден.
     * @return ссылка на шпиндель
     */
    Spindel& getSpindel(QString uid);

    /// Класс-друг!
    friend class MachineTool;

signals:
    void errorOccurred(ERROR_CODE code);

public slots:

private slots:
};

#endif // REPOSITORY_H
