#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include <QObject>

#include "presenters/mainwindowpresenter/mainwindowbridge/mainwindowbridge.h"
#include "models/serverconnectionmanager/serverconnectionmanager.h"

#include "models/devicesmanager/devicesmanager.h"
#include "models/sensorsmanager/sensorsmanager.h"
#include "models/settingsmanager/settingsmanager.h"
#include "models/pointsmanager/pointsmanager.h"
#include "models/filesmanager/gcodesfilesmanager/gcodesfilesmanager.h"
#include "models/gcodesmanager/gcodesmanager.h"
#include "models/axisesmanager/axisesmanager.h"


/*!
 * \brief Класс Контроллер главного окна
 * Отвечает за всю логику работы с элементами главного окна
 */
class MainWindowPresenter : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса Контроллер главного окна
     * \param parent - указатель на объект (по умолчанию равен nullptr)
     */
    explicit MainWindowPresenter(QObject *parent = nullptr);

    /*!
      * \brief Деструктор класса Контроллер главного окна
      */
    ~MainWindowPresenter();

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
    QStringList getAxisesParametrsNames();
    QList<QStringList> getAxisesSettings();

    QStringList getOptionsNames();


    unsigned int getVelocity();
    unsigned int getSpindelRotations();

    QList<QStringList> getPoints();
    QStringList getPoint(unsigned int number);

    QString getFilePath(QString type = "gcodes");
    void exportSettings();
    void importSettings();

    void parseGCodes(QString data);

    size_t getFeedrate() const;

    size_t getRotations() const;

protected:
    QWidget* m_widget;

    SettingsManager* m_settingsManager;
    ServerConnectionManager* m_serverManager;

    SensorsManager* m_sensorsManager;
    DevicesManager* m_devicesManager;
    AxisesManager* m_axisesManager;

    GCodesFilesManager* m_gcodesFilesManager;
    GCodesManager* m_gcodesManager;

    PointsManager* m_pointsManager;

    size_t feedrate = 50;
    size_t rotations = 2000;

signals:
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

    void receivedMessage(QString message);

    void machineToolIsConnected();
    void machineToolIsDisconnected(QString message = "");

    void gcodesLoadingStart();
    void gcodesIsLoading(int value);
    void gcodesLoaded();

public slots:

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

    void sendTextMessgeToServer(QString message);
    void sendBinaryMessageToServer(QByteArray message);
    void onMessageReceived(QString message);
    void onMessageReceived(QByteArray message);

    void onConnected();
    void onDisconnected(QString message);

    void openWebSocketConnection();
    void closeWebSocketConnection();

    void onGCodesLoadingStart();
    void onGCodesLoading(int currentValue);
    void onGCodesLoaded();
};

#endif // MAINWINDOWPRESENTER_H
