#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QTreeWidgetItem>

#include "models/machinetool/machinetool.h"
#include "models/serverconnector/serverconnectionmanager.h"

//#include "models/machinetool/commandsmanager/commands/smlcommandsbuilder.h"

#include "controllers/mainwindowcontroller/mainwindowbridge/mainwindowbridge.h"
//#include "controllers/programvisualizewindowcontroller/programvisualizewindowcontroller.h"


/*!
 * \brief Класс Контроллер главного окна
 * Отвечает за всю логику работы с элементами главного окна
 */
class MainWindowController : public QObject
{
    Q_OBJECT

protected:
    /*!
     * \brief Указатель на станок, к которому требуется подключиться
     */
    MachineTool* machineTool;
    ServerConnectionManager* serverManager;
    /*!
     * \brief Указатель на мост для связи с классом Главное окно
     */
    MainWindowBridge* mainWindowBridge;

public:
    /*!
     * \brief Конструктор класса Контроллер главного окна
     * \param parent - указатель на объект (по умолчанию равен nullptr)
     */
    explicit MainWindowController(QObject *parent = nullptr);

    /*!
      * \brief Деструктор класса Контроллер главного окна
      */
    ~MainWindowController();

    QStringList getSensorsNames();
    QStringList getSensorsParametrsNames();
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

    //int getCommandId(QString commandName);
    //size_t getCommandsCount();
    //void insertCommand(int id, QStringList arguments, size_t index);
    //QList<QTreeWidgetItem*> getCommands();
    //QStringList getCommandArguments(size_t index);
    //void updateCommand(QStringList arguments, size_t index);

    void exportSettings();
    void importSettings();

    void parseGCodes(QString data);

    void setServerDebug(bool debug);

signals:
    /// Настройки станка загружены
    void machineToolSettingsIsLoaded();

    /// Обновлено состояние станка
    void machineToolStateIsChanged();

    /// Точки обновились
    void pointsUpdated();

    /// Команды обновились
    //void commandsUpdated();

    /// Обновились G-коды
    void gcodesUpdated();

    void filePathUpdated();

    void receivedDebugMessage(QString message);

    void machineToolIsConnected();
    void machineToolIsDisconnected(QString message);

public slots:
    /// Слот для загрузки насроек станка
    void loadMachineToolSettings();

    /// Слот для испускания сигнала об обновлении состояния станка
    void updateMachineToolState();

    void setupMainWindowBridge();

    void setupServerConnection();

    /// Слот для настройки подключения к контроллеру U1
    //void setupU1Connection();

    /// Слот для настройки подключения к контроллеру KFlop
    //void setupKFlopConnection();

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

    void testServer(bool on = true);
    void sendTextMessgeToServer(QString message);
    void sendBinaryMessageToServer(QByteArray message);
    void handleDebugMessage(QString debugMessage);
    void handleDebugMessage(QByteArray debugMessage);

    void handleServerIsConnected();
    void handleServerIsDisconnected(QString message);

    void openWebSocketConnection();
    void stopWebSocketServer();


    //friend class ProgramVisualizeWindowController;
};

#endif // MAINWINDOWCONTROLLER_H
