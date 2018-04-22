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
 * Отвечает за всю логику приложения
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
    QWidget* m_widget;

    SettingsManager* m_settingsManager;
    ServerManager* m_serverManager;

    SensorsManager* m_sensorsManager;
    DevicesManager* m_devicesManager;
    AxisesManager* m_axisesManager;

    GCodesFilesManager* m_gcodesFilesManager;
    GCodesManager* m_gcodesManager;

    PointsManager* m_pointsManager;

    bool m_u1Connected;
    bool m_u2Connected;

    size_t feedrate = 50;
    size_t rotations = 2000;

    void setup();

signals:
    void u1Connected();
    void u2Connected();

    void u1Disconnected();
    void u2Disconnected();

    /// Обновлено состояние станка
    void u1StateIsChanged();
    void u2StateIsChanged();

    /// Точки обновились
    void pointsUpdated();

    /// Команды обновились
    //void commandsUpdated();

    /// Обновились G-коды
    void gcodesUpdated();

    void filePathUpdated();

    void gcodesLoadingStart();
    void gcodesIsLoading(int value);
    void gcodesLoaded();

public slots:

    void startServer();
    void stopServer();

    void onU1Connected();
    void onU1Disconnected();

    /// Слот для испускания сигнала об обновлении состояния станка
    void updateU1State();

    void switchDevice(QString deviceName);
    void updateVelocity(int value);
    void updateSpindelRotations(int value);


    void addPoint(QStringList coordinates);
    void updatePoint(QStringList coordinates, unsigned int number);
    void deletePoint(unsigned int number);

    //void deleteCommand(unsigned int number);
    //std::vector<std::shared_ptr<SMLCommand> > interpretCommands();

    /*void newSMLFile();
    void openSMLFile();
    void saveSMLFile();
    void saveSMLFileAs();
    void addSMLFile();*/

    void openGCodesFile();
    QString getGCodesFileContent();
    void saveGCodesFile(const QString data);
    void saveGCodesFileAs(const QString data);
    void newGCodesFile();
    void addGCodesFile(const QString data);
    void updateGCodes(const QString &data);
    QString getGCodesProgram();

    QList<Point> getMachineToolCoordinates();

    void onGCodesLoadingStart();
    void onGCodesLoading(int currentValue);
    void onGCodesLoaded();

    QStringList getSensorsLabels();
    QStringList getSensorParametrLabels();
    QList<QStringList> getSensorsSettings();
    QList<QColor> getSensorsLeds();
    QStringList getDevicesNames();
    QStringList getDevicesParametrsNames();
    QList<QStringList> getDevicesSettings();
    QStringList getOnScreenDevicesNames();
    QList<bool> getOnScreenDevicesStates();

    QStringList getAxisesNames();
    QStringList getAxisesSettings();

    QStringList getOptionsNames();

    QList<QStringList> getPoints();
    QStringList getPoint(unsigned int number);

    QString getFilePath(QString type = "gcodes");
    void exportSettings();
    void importSettings();

    void parseGCodes(QString data);

    size_t getFeedrate() const;

    size_t getSpindelRotations() const;

    void setSoftLimitsMode(bool enable);

    QStringList getCurrentConnections();

    QString getServerPort();
    QString getSensorsBufferSize();
    QString getDevicesBufferSize();
};

#endif // MACHINETOOL_H
