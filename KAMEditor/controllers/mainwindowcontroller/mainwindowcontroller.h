#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QTimer>

#include "models/structs.h"
#include "models/machinetool/machinetool.h"
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevicemanager.h"
#include "controllers/mainwindowcontroller/mainbridge/mainbridge.h"

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


    unsigned int getVelocity();
    unsigned int getSpindelRotations();

    QList<QStringList> getPoints();
    QStringList getPoint(unsigned int number);

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
#endif
    /*!
     * \brief Указатель на мост для связи с классом Главное окно
     */
    MainBridge* mainBridge;

    /// Таймер для обновления
    QTimer *timer;

signals:
    /// Настройки станка загружены
    void machineToolSettingsIsLoaded();

    /// Контроллер u1 подключен
    void u1IsConnected();

    /// Контроллер u1 отключен
    void u1IsDisconnected();

    /// Обновлено состояние станка
    void machineToolStateIsChanged();

    /// Точки обновились
    void pointsUpdated();

public slots:
    /// Слот для загрузки насроек станка
    void loadMachineToolSettings();

    /// Слот для подключения к контроллеру U1
    void connectWithU1();

    /// Слот для испускания сигнала об обновлении состояния станка
    void updateMachineToolState();

    /// Слот для настройки таймера обновления дисплеев
    void setupTimer();

    void setupMainBridge();

    void setupU1Connection();

    void switchDevice(QString qDeviceName);
    void updateVelocity(int value);
    void updateSpindelRotations(int value);


    void addPoint(QStringList coordinates);
    void updatePoint(QStringList coordinates, unsigned int number);
    void deletePoint(unsigned int number);
};

#endif // MAINWINDOWCONTROLLER_H
