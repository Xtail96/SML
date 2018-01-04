#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QTreeWidgetItem>

#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/smlcommandsbuilder.h"
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevicemanager.h"
#include "models/controllerconnector/kflopmanager/kflopmanager.h"

#include "controllers/mainwindowcontroller/mainwindowbridge/mainwindowbridge.h"
#include "controllers/programvisualizewindowcontroller/programvisualizewindowcontroller.h"


/*!
 * \brief Класс Контроллер главного окна
 * Отвечает за всю логику работы с элементами главного окна
 */
class MainWindowController : public QObject
{
    Q_OBJECT

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

    int getCommandId(QString commandName);
    size_t getCommandsCount();
    void insertCommand(int id, QStringList arguments, size_t index);

    QList<QTreeWidgetItem*> getCommands();
    QStringList getCommandArguments(size_t index);
    void updateCommand(QStringList arguments, size_t index);

    void exportSettings(QString path);
    void importSettings(QString path);

    void parseGCodes(QString data);

protected:
    /*!
     * \brief Указатель на станок, к которому требуется подключиться
     */
    MachineTool* machineTool;
#ifdef Q_OS_WIN
    /*!
     * \brief Указатель на класс для взаимодействия с контроллером u1 по usb
     * \warning с помощью данного объекта, взаимодействие по usb осуществляется только в операционной системе windows
     */
    UsbXpressDeviceManager* u1Manager;

    /*!
     * \brief Указатель на класс для взаимодействия с контроллером KFlop по usb
     * \warning с помощью данного объекта, взаимодействие по usb осуществляется только в операционной системе windows
     */
    KFlopManager* kflopManager;
#endif
    /*!
     * \brief Указатель на мост для связи с классом Главное окно
     */
    MainWindowBridge* mainWindowBridge;

    /// Таймер для обновления
    QTimer *timer;

signals:
    /// Настройки станка загружены
    void machineToolSettingsIsLoaded();

    /// Контроллер u1 подключен
    void u1IsConnected();

    /// Контроллер u1 отключен
    void u1IsDisconnected();

    /// Контроллер KFlop подключен
    void kflopIsConnected();

    /// Контроллер KFlop отключен
    void kflopIsDisconnected();

    /// Обновлено состояние станка
    void machineToolStateIsChanged();

    /// Точки обновились
    void pointsUpdated();

    /// Команды обновились
    void commandsUpdated();

    void gcodesUpdated();

public slots:
    /// Слот для загрузки насроек станка
    void loadMachineToolSettings();

    /// Слот для подключения к контроллеру U1
    void connectWithU1();

    /// Слот для подключения к контроллеру KFlop
    void connectWithKFlop();

    /// Слот для испускания сигнала об обновлении состояния станка
    void updateMachineToolState();

    /// Слот для настройки таймера обновления дисплеев
    void setupTimer();

    void setupMainWindowBridge();

    /// Слот для настройки подключения к контроллеру U1
    void setupU1Connection();

    /// Слот для настройки подключения к контроллеру KFlop
    void setupKFlopConnection();

    void switchDevice(QString qDeviceName);
    void updateVelocity(int value);
    void updateSpindelRotations(int value);


    void addPoint(QStringList coordinates);
    void updatePoint(QStringList coordinates, unsigned int number);
    void deletePoint(unsigned int number);

    void deleteCommand(unsigned int number);

    std::vector<std::shared_ptr<SMLCommand> > interpretCommands();

    void newSMLFile();
    void openSMLFile();
    void saveSMLFile();
    void saveSMLFileAs();
    void addSMLFile();

    void openGCodesFile();
    QString getGCodesFileContent();

    friend class ProgramVisualizeWindowController;
};

#endif // MAINWINDOWCONTROLLER_H
