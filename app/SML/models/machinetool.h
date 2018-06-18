#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>

#include "models/repository/repository.h"
#include "models/types/server/smlserver.h"

#include "models/services/connections/connectionsmonitor.h"


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
    QScopedPointer<Repository> m_repository;
    QScopedPointer<SMLServer> m_server;

    QScopedPointer<ConnectionsMonitor> m_connectionMonitor;

    /// Подключает нужные слоты к полям и сигналам класса
    void setupConnections();

    /// Отключает слоты от полей и сигналов класса
    void resetConnections();

signals:
    void u1Connected();
    void u1Disconnected();
    void u1Error(int code);
    void sensorStateChanged(QString sensorName, QColor color);

public slots:
    void onSensorStateChanged(QString sensorName, bool state);

    /// Производит запуск сервера
    void startServer();

    /// Производит остановку сервера
    void stopServer();

    /// Включает устройство
    void switchSpindelOn(QString spindelName, size_t rotations);
    void switchSpindelOff(QString spindelName);
protected slots:
    /// пишем даные в репозиторий
    void onServer_U1Connected();
    void onServer_U1Disconnected();
    void onServer_U1Error(int errorCode);
    void onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, int error);

    /// обрабатываем данные от монитора
    void onConnectionMonitor_U1Connected();
    void onConnectionMonitor_U1Disconnected();
    void onConnectionMonitor_U1Error(int code);


/////////////////////////////////////////////////////////////


public slots:
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

    QStringList getSensorNames();
    QMap<QString, QString> getSensorSettings(QString name);

    /// Устанавливает текущее значение G-Codes
    void setGCodes(const QString &data);
    /// Возвращает текущее значение G-Codes
    QString getGCodesProgram();

    /// Возвращает содержимое файла G-Codes
    QString getGCodesFileContent();

    /// Возвращает текущие координаты станка
    QList<Point> getMachineToolCoordinates();

    /// Вовращает значения настроей подключенных датчиков
    QStringList getSensorsSettings();

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

    QList<Spindel *> getSpindels();

protected slots:


    /// Обрабатывает событие изменения состояния U1
    void updateU1State();

    /// Обрабатывает ошибки в работе станка
    void handleMachineToolErrors(int errorCode);

    /// Обрабатывает событие окончания загрузки файла G-Codes
    void onGCodesLoaded();
};

#endif // MACHINETOOL_H
