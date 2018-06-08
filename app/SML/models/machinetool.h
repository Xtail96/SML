#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>

#include "models/serverManager/servermanager.h"

#include "models/devicesmanager/devicesmanager.h"
#include "models/sensorsmanager/sensorsmanager.h"
#include "models/settingsmanager/settingsmanager.h"
#include "models/pointsmanager/pointsmanager.h"
#include "models/filesmanager/gcodesfilesmanager/gcodesfilesmanager.h"
#include "models/gcodesmanager/gcodesmanager.h"
#include "models/axisesmanager/axisesmanager.h"


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

protected:
    /// Менеджер настроек
    QScopedPointer<SettingsManager> m_settingsManager;

    /// Менеджер управления сервером
    QScopedPointer<ServerManager> m_serverManager;

    /// Менеджер для работы с датчиками
    QScopedPointer<SensorsManager> m_sensorsManager;

    /// Менеджер для работы с устройствами
    QScopedPointer<DevicesManager> m_devicesManager;

    /// Менеджер для управления осями
    QScopedPointer<AxisesManager> m_axisesManager;

    /// Менеджер для управления файлами в G-Codes
    QScopedPointer<GCodesFilesManager> m_gcodesFilesManager;

    /// Менеджер обработки G-Codes
    QScopedPointer<GCodesManager> m_gcodesManager;

    /// Менеджер для работы с точками
    QScopedPointer<PointsManager> m_pointsManager;

    /// Флаг подключения адаптера контроллера датчиков и устройств
    bool m_u1Connected;

    /// Флаг подключения адптера контроллера движения
    bool m_u2Connected;

    /// Скорость перемещени ?
    size_t feedrate = 50;

    /// Обороты шпинделя ?
    size_t rotations = 2000;

    /// Подключает нужные слоты к полям и сигналам класса
    void setupConnections();

    /// Отключает слоты от полей и сигналов класса
    void resetConnections();

signals:
    /// Сигнал подключения адаптера контроллера датчиков и устройств
    void u1Connected();

    /// Сигнал отключения адаптера контроллера датчиков и устройств
    void u1Disconnected();

    /// Обновлено состояние датчиков и устрйоств
    void u1StateIsChanged();

    /// Сигнал подключения адаптера контроллера движения
    void u2Connected();

    /// Сигнал отключения адаптера контроллера движения
    void u2Disconnected();

    /// Обновлено состояния осей
    void u2StateIsChanged();

    /// В работе программы возникли ошибки
    void machineToolErrorIsOccured(int errorCode);

    /// Точки обновились
    void pointsUpdated();

    /// Команды обновились
    //void commandsUpdated();

    /// Обновились G-коды
    void gcodesUpdated();

    /// Обновился путь до файла с G-Codes
    void filePathUpdated();

public slots:
    /// Производит запуск сервера
    void startServer();

    /// Производит остановку сервера
    void stopServer();

    /// Включает устройство
    void switchSpindelOn(QString spindelName, size_t rotations);
    void switchSpindelOff(QString spindelName);

    /// Обновляет значение скорости пермещения
    void updateVelocity(int value);

    /// Обвновляет значение оборотв шпинделя
    void updateSpindelRotations(int value);

    /// Производит добавление точки
    void addPoint(QStringList coordinates);

    /// Производит обновление точки
    void updatePoint(QStringList coordinates, unsigned int number);

    /// Производит удаление точки
    void deletePoint(unsigned int number);

    //void deleteCommand(unsigned int number);
    //std::vector<std::shared_ptr<SMLCommand> > interpretCommands();

    /*void newSMLFile();
    void openSMLFile();
    void saveSMLFile();
    void saveSMLFileAs();
    void addSMLFile();*/

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

    /// Производит парсинг G-Codes
    void parseGCodes();

    /// Производит экспорт настроек станка в *.ini файл
    void exportSettings();

    /// Производит импорт настроек станка из *.ini файла
    void importSettings();

    /// set-еры и get-еры

    /// Устанавливает текущее значение G-Codes
    void setGCodes(const QString &data);
    /// Возвращает текущее значение G-Codes
    QString getGCodesProgram();

    /// Возвращает содержимое файла G-Codes
    QString getGCodesFileContent();

    /// Возвращает текущие координаты станка
    QList<Point> getMachineToolCoordinates();

    /// Возвращает имена датчиков в виде списка
    QStringList getSensorsLabels();

    /// Возвращает текущие цвета индикаторов подключенных датчиков
    QList<QColor> getSensorsLeds();

    /// Возвращает названия настроек дачтков
    QStringList getSensorParametrLabels();

    /// Вовращает значения настроей подключенных датчиков
    QList<QStringList> getSensorsSettings();

    /// Возвращает список подключенных устройств
    QStringList getDevicesNames();

    /// Возвращает список названий параметров устройств
    QStringList getDevicesParametrsNames();

    /// Возвращает настройки подключенных устройств
    QList<QStringList> getDevicesSettings();

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

    /// Возвращает список точек
    QList<QStringList> getPoints();

    /// Возвращает координаты точки по ее индексу
    QStringList getPoint(unsigned int number);

    /// Возвращает путь до открытого файла
    QString getFilePath(QString type = "gcodes");

    /// Возвращает текущее значение скорости
    size_t getFeedrate() const;

    /// Возвращает текущее значение оборотов шпинделя
    size_t getSpindelRotations() const;

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

    QList<Spindel> getSpindels();

protected slots:

    /// Обрабатывает событие подключения адаптера U1
    void onU1Connected();

    /// Обрабатывает событие отключения адаптера U1
    void onU1Disconnected();

    /// Обрабатывает событие ошибки адаптера U1
    void onU1Error(int errorCode);

    /// Обрабатывает событие изменения состояния U1
    void updateU1State();

    /// Обрабатывает ошибки в работе станка
    void handleMachineToolErrors(int errorCode);

    /// Обрабатывает событие окончания загрузки файла G-Codes
    void onGCodesLoaded();
};

#endif // MACHINETOOL_H
