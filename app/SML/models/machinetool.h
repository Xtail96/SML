#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <QObject>

#include "models/repository/repository.h"
#include "models/types/server/smlserver.h"

#include "models/services/connections/connectionsmonitor.h"
#include "models/services/points/pointsmonitor.h"
#include "models/services/sensors/sensorsmonitor.h"


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

protected:
    QScopedPointer<Repository> m_repository;
    QScopedPointer<SMLServer> m_server;

    QScopedPointer<ConnectionsMonitor> m_connectionMonitor;
    QScopedPointer<PointsMonitor> m_pointsMonitor;
    QScopedPointer<SensorsMonitor> m_sensorsMonitor;

    /// Подключает нужные слоты к полям и сигналам класса
    void setupConnections();

    /// Отключает слоты от полей и сигналов класса
    void resetConnections();

signals:
    void u1Connected();
    void u1Disconnected();
    void u1Error(int code);
    void sensorStateChanged(QString sensorName, QColor color);

    void pointsUpdated();

public slots:

protected slots:
    /// пишем даные в репозиторий
    void onServer_U1Connected();
    void onServer_U1Disconnected();
    void onServer_U1Error(int errorCode);
    void onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, int error);

    /// обрабатываем данные от монитора
    void onConnectionMonitor_U1Connected();
    void onConnectionMonitor_U1Disconnected();
    void onConnectionMonitor_U1LastErrorChanged(int code);

    void onPointsMonitor_PointsUpdated();

    void onSensorMonitor_StateChanged(QString sensorName, bool state);

/////////////////////////////////////////////////////////////


public slots:

    /// Включает устройство
    void switchSpindelOn(QString spindelName, size_t rotations);
    void switchSpindelOff(QString spindelName);

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

protected slots:
    /// Обрабатывает событие окончания загрузки файла G-Codes
    void onGCodesLoaded();
};

#endif // MACHINETOOL_H
